#pragma once

#include <memory>
#include <vector>

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>

#include "programs/stereoblitprogram.h"
#include "etc/contextdependant.h"

#include "view.h"
#include "stereovieweye.h"
#include "screenblitter.h"


class StereoView: public View, public ContextDependant {
public:
    StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo);

    virtual void setViewport(const Viewport& viewport) override;

    virtual float fovy() const override;
    virtual float zNear() const override;
    virtual float aspectRatio() const override;

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    StereoViewEye m_leftEye;
    StereoViewEye m_rightEye;
    ScreenBlitter m_screenBlitter;
    std::unique_ptr<StereoBlitProgram> m_stereoBlitProgram;

    glm::vec2 m_leftEyeLensCenter;
    glm::vec2 m_rightEyeLensCenter;
    std::vector<float> m_distortionKs;
    float m_distortionScale;

    void initialize();

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

