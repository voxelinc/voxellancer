#pragma once

#include <string>

#include "display/eyeside.h"


class FrameBuffer;
class Camera;

class RenderPass {
public:
    RenderPass(const std::string& name);

    virtual void update(float deltaSec) = 0;
    virtual void apply(FrameBuffer& frameBuffer, Camera& camera, EyeSide side) = 0;
    const std::string& name() const;


protected:
    std::string m_name;

};
