#pragma once

#include <glm/glm.hpp>


class OculusInfo {
public:
    float hScreenSize() const;
    float vScreenSize() const;

    float vScreenCenter() const;

    float eyeToScreenDistance() const;

    float lensSeparationDistance() const;

    float interpupillaryDistance() const;

    int hResolution() const;
    int vResolution() const;
};
