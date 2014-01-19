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
    StereoView(const StereoRenderInfo& stereoRenderInfo);

    void resize();

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    StereoViewEye m_leftEye;
    StereoViewEye m_rightEye;
    ScreenBlitter m_screenBlitter;
    StereoBlitProgram m_stereoBlitProgram;

    float m_leftEyeLensCenter;
    float m_rightEyeLensCenter;
};

