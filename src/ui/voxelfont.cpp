#include "voxelfont.h"

#include <algorithm>

#include "resource/clustercache.h"
#include "voxel/voxelrenderer.h"
#include "letter.h"

VoxelFont *VoxelFont::s_instance = nullptr;

VoxelFont::VoxelFont():
    m_font3x5(),
    m_font5x7()
{
    loadFont("3x5", glm::vec3(1, 2, 0), &m_font3x5);
    loadFont("5x7", glm::vec3(2, 3, 0), &m_font5x7);
}

VoxelFont::~VoxelFont(){
}

void VoxelFont::loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<Letter>> *map) {
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

void VoxelFont::loadChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<Letter>> *map){
    std::unique_ptr<Letter> element(new Letter(1.0));
    ClusterCache::instance()->fillCluster(element.get(), filename);
    element->transform().setCenter(offset);
    (*map)[index] = move(element);
}

void VoxelFont::drawString(std::string text, glm::vec3 position, glm::quat orientation, FontSize size, float scale, FontAlign align) {
    assert(VoxelRenderer::instance()->prepared());

    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::map<char, std::unique_ptr<Letter>> *source;
    float width;
    float intoffset;
    switch (size) {
        case FontSize::SIZE5x7:
            source = &m_font5x7;
            width = 7 * scale;
            break;
        case FontSize::SIZE3x5:
        default:
            source = &m_font3x5;
            width = 5 * scale;
            break;
    }
    switch (align) {
        case FontAlign::RIGHT:
            intoffset = -1.f * (text.length() - 1) * width;
            break;
        case FontAlign::CENTER:
            intoffset = -1.f * ((text.length() - 1) / 2.0f) * width;
            break;
        case FontAlign::LEFT:
        default:
            intoffset = 0;
            break;
    }

    for (int i = 0; i < text.length(); i++) {
        Letter *cl = (*source)[text[i]].get();
        if (cl != nullptr) {
            cl->transform().setPosition(position + orientation*glm::vec3(intoffset + width * i, 0, 0));
            cl->transform().setOrientation(orientation);
            cl->transform().setScale(scale);
            VoxelRenderer::instance()->draw(*cl);
        }
    }
}

int VoxelFont::letterWidth(FontSize size) {
    switch (size) {
        case FontSize::SIZE3x5:
            return 5;
        case FontSize::SIZE5x7:
            return 7;
        default:
            assert(false);
    }
    return 0;
}

int VoxelFont::letterHeight(FontSize size) {
    switch (size) {
        case FontSize::SIZE3x5:
            return 5;
        case FontSize::SIZE5x7:
            return 7;
        default:
            assert(false);
    }
    return 0;
}

VoxelFont* VoxelFont::instance() {
    if (s_instance == nullptr) {
        s_instance = new VoxelFont();
    }

    return s_instance;
}
