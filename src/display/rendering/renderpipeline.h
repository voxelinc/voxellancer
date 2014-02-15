#pragma once

#include <vector>
#include <memory>

#include "renderpass.h"
#include "display/eyeside.h"


class FrameBuffer;
class Player;
class Camera;

class RenderPipeline : public RenderPass {
public:
    RenderPipeline(const std::string& name);

    virtual void update(float deltaSec);
    virtual void apply(FrameBuffer& frameBuffer, const Camera& camera, EyeSide side) override;
    virtual void setup() = 0;
    virtual int bufferCount() = 0;

    void add(std::shared_ptr<RenderPass> pass, int index = -1);
    void insertAfter(std::shared_ptr<RenderPass> pass, const std::string& after);

    static RenderPipeline* getDefault(Player* player);


protected:
    std::vector<std::shared_ptr<RenderPass>> m_passes;
};

