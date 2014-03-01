#pragma once

#include <list>
#include <string>
#include <glm/glm.hpp>

#include "input/inputmapping.h"

class PropertyConverter {
public:
    static glm::vec2 vec2Converter(const std::string &s);
    static glm::vec3 vec3Converter(const std::string &s);
    static glm::vec4 vec4Converter(const std::string &s);
    static std::list<std::string> listConverter(const std::string &s);
    static InputMapping inputMappingConverter(const std::string &s);
};