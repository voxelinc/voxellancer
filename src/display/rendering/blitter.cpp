#include "blitter.h"

#include <glow/FrameBufferObject.h>

#include "quad.h"
#include "framebuffer.h"


Blitter::Blitter() :
    PostProcessingPass("blitter", *new Quad())
{
    setInput({ BufferName::Default });
    setOutput({ BufferName::Default });
    setSamplers({ "source" });
    setFragmentShader("data/shader/blit.frag");
}

void Blitter::apply(FrameBuffer& frameBuffer, glow::FrameBufferObject* target) {
    if (!m_program) {
        initialize();
    }

    beforeDraw(frameBuffer);
    target->bind(GL_DRAW_FRAMEBUFFER);

    m_program->use();
    m_quad.draw();
    m_program->release();
}
