#include "viewer.h"

#include <iostream>

#include "camera/camerahead.h"

#include "scene.h"
#include "stereorenderinfo.h"
#include "monoview.h"
#include "stereoview.h"


Viewer::Viewer(const Viewport& viewport):
    m_view(nullptr),
    m_cameraHead(nullptr),
    m_viewport(viewport),
    m_scene(nullptr)
{
    switchToMonoView();
}

Scene* Viewer::scene() {
    return m_scene;
}

void Viewer::setScene(Scene* scene) {
    if (m_scene) {
        m_scene->deactivate();
    }
    m_scene = scene;
    scene->activate();
    scene->setViewportResolution(Size<int>(m_viewport.width(), m_viewport.height()));
}

void Viewer::setCameraHead(CameraHead* cameraHead) {
    m_cameraHead = cameraHead;
}

void Viewer::setViewport(const Viewport& viewport) {
    m_viewport = viewport;
    if (m_view) {
        m_view->setViewport(viewport);
    }
    if (m_scene) {
        m_scene->setViewportResolution(Size<int>(viewport.width(), viewport.height()));
    }
}

void Viewer::switchToMonoView() {;
    m_view = std::unique_ptr<View>(new MonoView(m_viewport));
}

void Viewer::switchToStereoView(const StereoRenderInfo& stereoRenderInfo) {
    m_view = std::unique_ptr<View>(new StereoView(m_viewport, stereoRenderInfo));
}

void Viewer::draw() {
    m_view->draw(m_scene, m_cameraHead);
}

void Viewer::update(float deltaSec) {
    m_scene->update(deltaSec);
}

