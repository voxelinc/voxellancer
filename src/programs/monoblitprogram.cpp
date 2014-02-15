#include "monoblitprogram.h"

#include <iostream>

#include <glow/Shader.h>
#include <glowutils/global.h>

#include "display/rendering/screenquad.h"


MonoBlitProgram::MonoBlitProgram() {

}

void MonoBlitProgram::initializeShaders() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/blit/monoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/blit/monoblit.frag");

    bindAttributeLocation(ScreenQuad::VERTEX_ATTRIBUTE_LOCATION, "v_vertex");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    setUniform("texture", BlitProgram::TEXTURE_LOCATION);
}

