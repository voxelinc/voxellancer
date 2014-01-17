#include "stereoblitprogram.h"

#include <iostream>

#include <glm/glm.hpp>

#include <glow/Shader.h>
#include <glowutils/File.h>


StereoBlitProgram::StereoBlitProgram() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/stereoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/stereoblit.frag");

    bindAttributeLocation(BlitProgram::VERTEX_LOCATION, "v_vertex");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    getUniform<GLint>("texture")->set(BlitProgram::TEXTURE_LOCATION);
}

void StereoBlitProgram::blit() {
    assert(m_distortionKs.size() == 4);

    glm::vec4 distortionVec(
        m_distortionKs[0],
        m_distortionKs[1],
        m_distortionKs[2],
        m_distortionKs[3]
    );

    getUniform<glm::vec4>("distortionKs")->set(distortionVec);

    BlitProgram::blit();
}

void StereoBlitProgram::setDistortionKs(std::vector<float> distortionKs) {
    m_distortionKs = distortionKs;
}

