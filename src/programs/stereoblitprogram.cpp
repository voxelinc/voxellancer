#include "stereoblitprogram.h"

#include <iostream>

#include <glm/glm.hpp>

#include <glow/Shader.h>
#include <glowutils/global.h>


StereoBlitProgram::StereoBlitProgram() {

}

void StereoBlitProgram::setDistortionKs(std::vector<float> distortionKs) {
    m_distortionKs = distortionKs;
}

void StereoBlitProgram::setDistortionScale(float distortionScale) {
    m_distortionScale = distortionScale;
}

void StereoBlitProgram::setLensCenter(glm::vec2 lensCenter) {
    m_lensCenter = lensCenter;
}

void StereoBlitProgram::blit() {
    assert(m_distortionKs.size() == 4);

    glm::vec4 distortionVec(
        m_distortionKs[0],
        m_distortionKs[1],
        m_distortionKs[2],
        m_distortionKs[3]
    );

    setUniform<glm::vec4>("distortionKs", distortionVec);
    setUniform<float>("distortionScale", m_distortionScale);
    setUniform<glm::vec2>("lensCenter", m_lensCenter);

    BlitProgram::blit();
}

void StereoBlitProgram::initializeShaders() {
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/stereoblit.vert");
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/stereoblit.frag");

    bindAttributeLocation(BlitProgram::VERTEX_LOCATION, "v_vertex");

    attach(vertShader, fragShader);
    link();
    assert(checkLinkStatus());

    bindFragDataLocation(0, "fragColor");

    getUniform<GLint>("texture")->set(BlitProgram::TEXTURE_LOCATION);
}

