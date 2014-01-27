#pragma once

class FrameBuffer;


class RenderPass {
public:
    RenderPass();

    virtual void apply(FrameBuffer& frameBuffer) = 0;
       
protected:


};