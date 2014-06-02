#include "introscene.h"

#include <glow/Program.h>

#include "camera/camera.h"

#include "display/rendering/skybox.h"

#include "ui/voxelfont.h"

#include "voxel/voxelrenderer.h"

#include "intro.h"


IntroScene::IntroScene(Intro& intro):
    m_intro(intro),
    m_font(VoxelFont::instance()),
    m_skybox(new Skybox("data/skybox/backen")),
    m_voxelRenderer(VoxelRenderer::instance())
{

}

IntroScene::~IntroScene() = default;

void IntroScene::update(float deltaSec) {

}

void IntroScene::drawImpl(const Camera& camera) const {
    m_skybox->draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", glm::vec3(0, 0, 1));

    m_voxelRenderer->prepareDraw(camera, false);
    VoxelFont::instance()->drawString("Voxellancer", glm::vec3(0, 0.5f, -1) * 40.f, glm::quat(), FontSize::SIZE5x7, 0.4f, FontAlign::CENTER);
    VoxelFont::instance()->drawString("Pre Alpha Version", glm::vec3(0, 0.3f, -1) * 40.f, glm::quat(), FontSize::SIZE5x7, 0.2f, FontAlign::CENTER);

    int lineNum = 0;
    for (const std::string& line : m_intro.lines()) {
        VoxelFont::instance()->drawString(line, glm::vec3(0, 0.1f - lineNum/10.0f, -1) * 40.f, glm::quat(), FontSize::SIZE5x7, 0.2f, FontAlign::CENTER);
        lineNum++;
    }

    m_voxelRenderer->afterDraw();
}

