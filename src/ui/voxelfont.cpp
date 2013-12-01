#include "voxelfont.h"

#include "resource/clustercache.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxelrenderer.h"

VoxelFont::VoxelFont() :
    m_renderer(nullptr),
    m_font3x5(),
    m_font5x7()
{
    loadFont("3x5", glm::vec3(1, 2, 0), &m_font3x5);
    loadFont("5x7", glm::vec3(2, 3, 0), &m_font5x7);
}

VoxelFont::~VoxelFont(){
}

void VoxelFont::loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<VoxelCluster>> *map){
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 36; i++){
        std::string path = "data/hud/font/" + identifier + "/";
        path.append(&letters[i], 1);
        path.append(".csv");
        loadChar(path, offset, letters[i], map);
    }
    // non-letters the fs might/does not like
    loadChar("data/hud/font/" + identifier + "/_dot.csv", offset, '.', map);
    loadChar("data/hud/font/" + identifier + "/_comma.csv", offset, ',', map);
    loadChar("data/hud/font/" + identifier + "/_colon.csv", offset, ':', map);
    loadChar("data/hud/font/" + identifier + "/_semicolon.csv", offset, ';', map);
    loadChar("data/hud/font/" + identifier + "/_slash.csv", offset, '/', map);
    loadChar("data/hud/font/" + identifier + "/_backslash.csv", offset, '\\', map);
    loadChar("data/hud/font/" + identifier + "/_underscore.csv", offset, '_', map);
    loadChar("data/hud/font/" + identifier + "/_dash.csv", offset, '-', map);
}

void VoxelFont::loadChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<VoxelCluster>> *map){
    std::unique_ptr<VoxelCluster> element(new VoxelCluster());
    ClusterCache::instance()->fillCluster(element.get(), filename);
    element->transform().setCenter(offset);
    (*map)[index] = move(element);
}

void VoxelFont::setRenderer(VoxelRenderer* renderer){
    m_renderer = renderer;
}

void VoxelFont::drawString(std::string text, glm::vec3 position, FontSize size, float scale, FontAlign align){
    assert(m_renderer);
    assert(m_renderer->prepared());
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::map<char, std::unique_ptr<VoxelCluster>> *source;
    float width;
    float intoffset;
    switch (size){
    case s5x7:
        source = &m_font5x7;
        width = 7 * scale;
        break;
    case s3x5:
    default:
        source = &m_font3x5;
        width = 5 * scale;
        break;
    }
    switch (align){
    case aRight:
        intoffset = -1.f * (text.length() - 1) * width;
        break;
    case aCenter:
        intoffset = -1.f * ((text.length() - 1) / 2.0f) * width;
        break;
    case aLeft:
    default:
        intoffset = 0;
        break;
    }

    for (int i = 0; i < text.length(); i++){
        VoxelCluster *cl = (*source)[text[i]].get();
        if (cl != nullptr){
            cl->transform().setPosition(position + glm::vec3(intoffset + width * i, 0, 0));
            cl->transform().setScale(scale);
            m_renderer->draw(cl);
        }
    }
}