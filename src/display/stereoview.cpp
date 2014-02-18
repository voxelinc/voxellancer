#include "stereoview.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "display/scene.h"
#include "display/stereorenderinfo.h"


StereoView::StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo):
    View(viewport),
    m_leftEye(glm::ivec2(viewport.width() / 2, viewport.height()), stereoRenderInfo, EyeSide::Left),
    m_rightEye(glm::ivec2(viewport.width() / 2, viewport.height()), stereoRenderInfo, EyeSide::Right),
    m_leftEyeLensCenter(stereoRenderInfo.leftEyeLensCenter()),
    m_rightEyeLensCenter(stereoRenderInfo.rightEyeLensCenter()),
    m_distortionKs(stereoRenderInfo.distortionKs()),
    m_distortionScale(stereoRenderInfo.distortionScale()),
    m_stereoBlitProgram(nullptr)
{
    initialize();
}

void StereoView::initialize() {
    m_stereoBlitProgram.reset(new StereoBlitProgram());

    m_stereoBlitProgram->setDistortionKs(m_distortionKs);
    m_stereoBlitProgram->setDistortionScale(m_distortionScale);

    m_screenBlitter.setProgram(m_stereoBlitProgram.get());
}

void StereoView::setViewport(const Viewport& viewport) {
    View::setViewport(viewport);

    m_leftEye.setViewportResolution(glm::ivec2(viewport.width() / 2, viewport.height()));
    m_rightEye.setViewportResolution(glm::ivec2(viewport.width() / 2, viewport.height()));
}

float StereoView::fovy() const {
    return m_leftEye.camera().fovy();
}

float StereoView::zNear() const {
    return m_leftEye.camera().zNear();
}

float StereoView::aspectRatio() const {
    return m_leftEye.camera().aspectRatio();
}

void StereoView::draw(const Scene& scene, const CameraHead& cameraHead) {
    m_leftEye.draw(scene, cameraHead);
    m_rightEye.draw(scene, cameraHead);

    glViewport(m_viewport.x(), m_viewport.y(), m_viewport.width(), m_viewport.height());

    m_stereoBlitProgram->setLensCenter(m_leftEyeLensCenter);
    m_screenBlitter.blit(m_leftEye.fbo(), Viewport(m_viewport.x(), m_viewport.y(), m_viewport.width() / 2, m_viewport.height()));

    m_stereoBlitProgram->setLensCenter(m_rightEyeLensCenter);
    m_screenBlitter.blit(m_rightEye.fbo(), Viewport(m_viewport.x() + m_viewport.width() / 2, m_viewport.y(), m_viewport.width() / 2, m_viewport.height()));
}

void StereoView::beforeContextDestroy() {
    m_stereoBlitProgram.reset();
}

void StereoView::afterContextRebuild() {
    initialize();
}
