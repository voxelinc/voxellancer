#pragma once

template<typename T>
void PostProcessingPass::setUniform(const std::string& name, const T& value) {
    if (!m_program) {
        initialize();
    }
    m_program->setUniform(name, value);
}
