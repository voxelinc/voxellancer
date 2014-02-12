#include "stereoview.h"

#include <iostream>

#include <GL/glew.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "display/scene.h"
#include "display/stereorenderinfo.h"
#include "stereovieweye.h"
#include "screenblitter.h"
#include "programs/stereoblitprogram.h"


StereoView::StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo):
    View(viewport),
    m_leftEye(new StereoViewEye(glm::ivec2(viewport.width() / 2, viewport.height()), stereoRenderInfo, EyeSide::Left)),
    m_rightEye(new StereoViewEye(glm::ivec2(viewport.width() / 2, viewport.height()), stereoRenderInfo, EyeSide::Right)),
    m_leftEyeLensCenter(stereoRenderInfo.leftEyeLensCenter()),
    m_rightEyeLensCenter(stereoRenderInfo.rightEyeLensCenter()),
    m_screenBlitter(new ScreenBlitter()),
    m_stereoBlitProgram(new StereoBlitProgram())
{
    m_stereoBlitProgram->setDistortionKs(stereoRenderInfo.distortionKs());
    m_stereoBlitProgram->setDistortionScale(stereoRenderInfo.distortionScale());

    m_screenBlitter->setProgram(*m_stereoBlitProgram);
}

void StereoView::setViewport(const Viewport& viewport) {
    View::setViewport(viewport);

    m_leftEye->setViewportResolution(glm::ivec2(viewport.width() / 2, viewport.height()));
    m_rightEye->setViewportResolution(glm::ivec2(viewport.width() / 2, viewport.height()));
}

float StereoView::fovy() const {
    return m_leftEye->camera().fovy();
}

float StereoView::zNear() const {
    return m_leftEye->camera().zNear();
}

float StereoView::aspectRatio() const {
    return m_leftEye->camera().aspectRatio();
}

void StereoView::draw(Scene* scene, CameraHead* cameraHead) {
    m_leftEye->draw(scene, cameraHead);
    m_rightEye->draw(scene, cameraHead);

    glViewport(m_viewport.x(), m_viewport.y(), m_viewport.width(), m_viewport.height());

    m_stereoBlitProgram->setLensCenter(m_leftEyeLensCenter);
    m_screenBlitter->blit(m_leftEye->fbo(), Viewport(m_viewport.x(), m_viewport.y(), m_viewport.width() / 2, m_viewport.height()));

    m_stereoBlitProgram->setLensCenter(m_rightEyeLensCenter);
    m_screenBlitter->blit(m_rightEye->fbo(), Viewport(m_viewport.x() + m_viewport.width() / 2, m_viewport.y(), m_viewport.width() / 2, m_viewport.height()));
}

