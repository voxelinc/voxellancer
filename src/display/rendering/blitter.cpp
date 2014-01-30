#include "blitter.h"

#include <glow/FrameBufferObject.h>

#include "screenquad.h"
#include "framebuffer.h"


Blitter::Blitter() :
    PostProcessingPass("blitter", std::make_shared<ScreenQuad>())
{
    setInputMapping({ { "source", 0 } });
    setOutput({ 0 });
    setFragmentShader("data/postprocessing/blit.frag");
}

void Blitter::apply(FrameBuffer& frameBuffer, glow::FrameBufferObject* target) {
    if (!m_program) {
        initialize();
    }

    beforeDraw(frameBuffer);
    target->bind(GL_DRAW_FRAMEBUFFER);

    m_program->use();
    m_quad->draw();
    m_program->release();
}
