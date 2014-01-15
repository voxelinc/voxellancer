#include "screenblitter.h"

#include <iostream>

#include <glow/Buffer.h>
#include <glow/FrameBufferAttachment.h>
#include <glow/TextureAttachment.h>
#include <glow/VertexAttributeBinding.h>

#include "programs/blitprogram.h"


ScreenBlitter::ScreenBlitter():
    m_blitProgram(nullptr)
{
}

void ScreenBlitter::setProgram(BlitProgram* blitProgram) {
    m_blitProgram = blitProgram;
}

void ScreenBlitter::blit(glow::FrameBufferObject& fbo, const Viewport& viewport) {
    m_blitProgram->setSource(&fbo);
    m_blitProgram->setDestination(glow::FrameBufferObject::defaultFBO(), viewport);
    m_blitProgram->blit();
}



