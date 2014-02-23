#pragma once

#include <memory>
#include <vector>

#include "view.h"
#include "etc/contextdependant.h"


class StereoViewEye;
class ScreenBlitter;
class StereoBlitProgram;
class ViewPort;
class StereoRenderInfo;

class StereoView: public View, public ContextDependant {
public:
    StereoView(const Viewport& viewport, const StereoRenderInfo& stereoRenderInfo);

    virtual void setViewport(const Viewport& viewport) override;

    virtual float fovy() const override;
    virtual float zNear() const override;
    virtual float aspectRatio() const override;

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    std::unique_ptr<StereoViewEye> m_leftEye;
    std::unique_ptr<StereoViewEye> m_rightEye;
    std::unique_ptr<ScreenBlitter> m_screenBlitter;
    std::unique_ptr<StereoBlitProgram> m_stereoBlitProgram;

    glm::vec2 m_leftEyeLensCenter;
    glm::vec2 m_rightEyeLensCenter;
    std::vector<float> m_distortionKs;
    float m_distortionScale;

    void initialize();

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

