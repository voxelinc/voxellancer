#pragma once

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>

#include "programs/stereoblitprogram.h"

#include "view.h"
#include "stereovieweye.h"
#include "screenblitter.h"


class StereoView: public View {
public:
    StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo);

    virtual void setViewport(const Viewport& viewport) override;

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    StereoViewEye m_leftEye;
    StereoViewEye m_rightEye;
    ScreenBlitter m_screenBlitter;
    StereoBlitProgram m_stereoBlitProgram;

    glm::vec2 m_leftEyeLensCenter;
    glm::vec2 m_rightEyeLensCenter;
};

