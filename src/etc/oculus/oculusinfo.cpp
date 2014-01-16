#include "oculusinfo.h"

float OculusInfo::hScreenSize() const {
    return 0.14976f;
}

float OculusInfo::vScreenSize() const {
    return 0.0935f;
}

float OculusInfo::vScreenCenter() const {
    return vScreenSize() / 2.0f;
}

float OculusInfo::eyeToScreenDistance() const {
    return 0.04f;
}

float OculusInfo::lensSeparationDistance() const {
    return 0.054f;
}

float OculusInfo::interpupillaryDistance() const {
    return 0.064f;
}

int OculusInfo::hResolution() const {
    return 1280;
}

int OculusInfo::vResolution() const {
    return 800;
}
