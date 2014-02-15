#pragma once

#include <string>

#include "display/eyeside.h"


class FrameBuffer;
class Camera;

class RenderPass {
public:
    RenderPass(const std::string& name);

    const std::string& name() const;

    virtual void update(float deltaSec) = 0;

    virtual void apply(FrameBuffer& frameBuffer, const Camera& camera, EyeSide side) = 0;


protected:
    std::string m_name;
};

