#pragma once

#include <glm/glm.hpp>

/* Class is in draft state - see github for discussion */
class Impact : public glm::vec3
{
public:
    using glm::vec3::vec3;

    const glm::vec3 &vec3() const;

    Impact &add(const Impact &impact);
};

