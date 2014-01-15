#include "monoblitprogram.h"

#include <iostream>

#include <glow/Shader.h>
#include <glowutils/File.h>


MonoBlitProgram::MonoBlitProgram() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/monoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/monoblit.frag");

    bindAttributeLocation(BlitProgram::VERTEX_LOCATION, "v_vertex");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    getUniform<GLint>("texture")->set(BlitProgram::TEXTURE_LOCATION);
}

