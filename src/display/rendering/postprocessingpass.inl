#pragma once

#include <glow/Program.h>


template<typename T>
void PostProcessingPass::setUniform(const std::string& name, const T& value) {
    if (!m_program) {
        initialize();
    }
    m_program->setUniform(name, value);
    if (!m_uniforms[name]) {
        m_uniforms[name] = m_program->getUniform<T>(name);
    }
}
