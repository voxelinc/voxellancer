#include "viewer.h"

#include "camera/camerahead.h"

#include "scene.h"
#include "stereorenderinfo.h"
#include "monoview.h"
#include "stereoview.h"


Viewer::Viewer():
    m_scene(nullptr),
    m_view(nullptr),
    m_cameraHead(nullptr)
{
    toMonoView();
}

void Viewer::setScene(Scene* scene) {
    m_scene = scene;
}

void Viewer::setCameraHead(CameraHead* cameraHead) {
    m_cameraHead = cameraHead;
}

void Viewer::toMonoView() {
    delete m_view;
    m_view = new MonoView();
}

void Viewer::toStereoView(const StereoRenderInfo& stereoRenderInfo) {
    delete m_view;
    m_view = new StereoView(stereoRenderInfo);
}

void Viewer::resized() {
    m_view->resized();
}

void Viewer::draw() {
    m_view->draw(m_scene, m_cameraHead);
}

