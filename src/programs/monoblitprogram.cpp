#include "monoblitprogram.h"

#include <iostream>

#include <glow/Shader.h>
#include <glowutils/global.h>


MonoBlitProgram::MonoBlitProgram() {

}

void MonoBlitProgram::initializeShaders() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/monoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/monoblit.frag");

    bindAttributeLocation(BlitProgram::VERTEX_LOCATION, "v_vertex");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    setUniform("texture", BlitProgram::TEXTURE_LOCATION);
}

