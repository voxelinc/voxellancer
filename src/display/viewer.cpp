#include "viewer.h"

#include <cassert>

#include <GL/glew.h>

#include "camera/camerahead.h"
#include "scene.h"
#include "stereorenderinfo.h"
#include "monoview.h"
#include "stereoview.h"


Viewer::Viewer(const Viewport& viewport):
    m_view(nullptr),
    m_viewport(viewport)
{
    switchToMonoView();
}

Viewer::~Viewer() = default;

const View& Viewer::view() const {
    return *m_view;
}

void Viewer::setViewport(const Viewport& viewport) {
    m_viewport = viewport;
    if (m_view) {
        m_view->setViewport(viewport);
    }
}

void Viewer::switchToMonoView() {
    m_view = std::unique_ptr<View>(new MonoView(m_viewport));
}

void Viewer::switchToStereoView(const StereoRenderInfo& stereoRenderInfo) {
    m_view = std::unique_ptr<View>(new StereoView(m_viewport, stereoRenderInfo));
}

void Viewer::draw(const Scene& scene, const CameraHead& cameraHead) {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_view->draw(scene, cameraHead);
}

void Viewer::update(float deltaSec) {

}

