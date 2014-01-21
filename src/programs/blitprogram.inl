#pragma once

template<typename T> 
void BlitProgram::setUniform(const std::string& name, const T& value) {
	if(!m_initialized) {
		initialize();
	}

	setUniform<T>(name, value);
}
