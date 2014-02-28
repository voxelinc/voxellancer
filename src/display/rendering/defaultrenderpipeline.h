#pragma once

#include <memory>
#include <vector>

#include "renderpipeline.h"


class FrameBuffer;
class RenderPass;
class ScreenQuad;

/*
   a renderpipeline that applies basic effects to the frame like
   a bloom effect and creates the final image
*/
class DefaultRenderPipeline : public RenderPipeline {
public:
    DefaultRenderPipeline();

    virtual void setup() override;
    virtual int bufferCount() override;

    void addEmissivenessBlurVertical();
    void addEmissivenessBlurHorizontal();
    void addFinalization();


protected:
    std::shared_ptr<ScreenQuad> m_quad;
};

