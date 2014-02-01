#pragma once

#include <memory>
#include <vector>

#include "renderpipeline.h"


class FrameBuffer;
class RenderPass;
class ScreenQuad;


class DefaultRenderPipeline : public RenderPipeline {
public:
    DefaultRenderPipeline(Player* player);

    virtual void setup() override;
    virtual int bufferCount() override;

    void addBlurVertical();
    void addBlurHorizontal();
    void addFinalization();
    
protected:
    std::shared_ptr<ScreenQuad> m_quad;
    Camera* m_camera;
    Player* m_player;
};
