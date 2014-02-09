#pragma once

#include "abstractmove.h"


class Speed: public AbstractMove {
public:
    Speed(const glm::vec3& directional, const glm::vec3& angular);
};

