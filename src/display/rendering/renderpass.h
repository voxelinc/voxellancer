#pragma once

#include <string>

#include "rendermetadata.h"


class FrameBuffer;
class Camera;

/*
   a step that adds something to the current frame
   can be postprocessing, geometry or any other effect
*/
class RenderPass {
public:
    RenderPass(const std::string& name);

    virtual void apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) = 0;
    const std::string& name() const;


protected:
    std::string m_name;
};

