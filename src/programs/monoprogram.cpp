#include "monoprogram.h"

#include <iostream>

#include <glow/Shader.h>
#include <glowutils/File.h>


MonoProgram::MonoProgram() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/monoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/monoblit.frag");

    bindAttributeLocation(0, "v_quadCoord");
//    bindAttributeLocation(1, "texture");
//    bindAttributeLocation(2, "offset");
//    bindAttributeLocation(3, "scale");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    getUniform<GLint>("texture")->set(0);
}

