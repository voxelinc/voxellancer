#include "stereoview.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "display/scene.h"
#include "display/stereorenderinfo.h"


StereoView::StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo):
    View(viewport),
    m_leftEye(Size<int>(viewport.width()/2, viewport.height()), stereoRenderInfo, StereoViewEye::Left),
    m_rightEye(Size<int>(viewport.width()/2, viewport.height()), stereoRenderInfo, StereoViewEye::Right),
    m_leftEyeLensCenter(stereoRenderInfo.leftEyeLensCenter()),
    m_rightEyeLensCenter(stereoRenderInfo.rightEyeLensCenter())
{
    m_stereoBlitProgram.setDistortionKs(stereoRenderInfo.distortionKs());
    m_stereoBlitProgram.setDistortionScale(stereoRenderInfo.distortionScale());

    m_screenBlitter.setProgram(&m_stereoBlitProgram);
}

void StereoView::setViewport(const Viewport& viewport) {
    View::setViewport(viewport);

    m_leftEye.setViewportResolution(Size<int>(viewport.width()/2, viewport.height()));
    m_rightEye.setViewportResolution(Size<int>(viewport.width()/2, viewport.height()));
}

void StereoView::draw(Scene* scene, CameraHead* cameraHead) {
    m_leftEye.draw(scene, cameraHead);
    m_rightEye.draw(scene, cameraHead);

    Viewport viewport = WindowManager::instance()->viewport();
    glViewport(0, 0, viewport.width(), viewport.height());

    m_stereoBlitProgram.setLensCenter(m_leftEyeLensCenter);
    m_screenBlitter.blit(m_leftEye.fbo(), Viewport(0, 0, viewport.width()/2, viewport.height()));

    m_stereoBlitProgram.setLensCenter(m_rightEyeLensCenter);
    m_screenBlitter.blit(m_rightEye.fbo(), Viewport(viewport.width()/2, 0, viewport.width()/2, viewport.height()));
}

