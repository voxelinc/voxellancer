#include "screenblitter.h"

#include <iostream>

#include "programs/blitprogram.h"
#include "programs/monoblitprogram.h"
#include "rendering/framebuffer.h"


ScreenBlitter::ScreenBlitter():
    m_blitProgram(new MonoBlitProgram())
{
}

void ScreenBlitter::setProgram(BlitProgram* blitProgram) {
    m_blitProgram = blitProgram;
}

void ScreenBlitter::blit(FrameBuffer& source, const Viewport& viewport) {
    m_blitProgram->setSource(source.texture(0));
    m_blitProgram->setDestination(glow::FrameBufferObject::defaultFBO(), viewport);
    m_blitProgram->blit();
}

