#pragma once

#include <string>

class FrameBuffer;


class RenderPass {
public:
    RenderPass(std::string name);

    virtual void apply(FrameBuffer& frameBuffer) = 0;
    const std::string& name() const;


protected:
    std::string m_name;

};
