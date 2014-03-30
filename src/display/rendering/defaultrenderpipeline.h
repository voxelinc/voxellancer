#pragma once

#include <memory>
#include <string>
#include <vector>

#include "renderpipeline.h"
#include "property/property.h"


class FrameBuffer;
class RenderPass;
class ScreenQuad;
class PostProcessingPass;

/*
   a renderpipeline that applies basic effects to the frame like
   a bloom effect and creates the final image
*/
class DefaultRenderPipeline : public RenderPipeline {
public:
    DefaultRenderPipeline();

    virtual void apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) override;
    virtual void setup() override;
    virtual int bufferCount() override;

    void addFXAA();
    void addEmissivenessBlurVertical();
    void addEmissivenessBlurHorizontal();
    void addFinalization();

protected:
    std::shared_ptr<ScreenQuad> m_quad;
    
    std::shared_ptr<PostProcessingPass> m_fxaa;
    std::shared_ptr<PostProcessingPass> m_finalization;
    Property<std::string> m_antialiasing;

};

