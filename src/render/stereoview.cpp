#include "stereoview.h"

#include "GL/glew.h"
#include "GL/gl.h"

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "render/scene.h"


StereoView::StereoView(const StereoRenderInfo& stereoRenderInfo):
    m_leftEye(stereoRenderInfo, StereoViewEye::Left),
    m_rightEye(stereoRenderInfo, StereoViewEye::Right)
{
    m_stereoBlitProgram.setDistortionKs(stereoRenderInfo.distortionKs());
    m_stereoBlitProgram.setDistortionScale(stereoRenderInfo.distortionScale());
    m_stereoBlitProgram.setLensCenter(stereoRenderInfo.lensCenter());

    m_screenBlitter.setProgram(&m_stereoBlitProgram);
}

void StereoView::resized() {
    m_leftEye.resized();
    m_rightEye.resized();
}

void StereoView::draw(Scene* scene, CameraHead* cameraHead) {
    m_leftEye.draw(scene, cameraHead);
    m_rightEye.draw(scene, cameraHead);

    Viewport viewport = WindowManager::instance()->viewport();
    glViewport(0, 0, viewport.width(), viewport.height());

    m_screenBlitter.blit(m_leftEye->fbo(), Viewport(0, 0, viewport.width()/2, viewport.height()));
    m_screenBlitter.blit(m_rightEye->fbo(), Viewport(viewport.width()/2, 0, viewport.width()/2, viewport.height()));
}

