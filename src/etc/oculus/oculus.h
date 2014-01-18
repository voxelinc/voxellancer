#pragma once

#include <memory>

#include <OVR.h>

#include <glow/ref_ptr.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "oculusinfo.h"


class Oculus {
public:
    Oculus(OVR::HMDDevice* hmdDevice);
    ~Oculus();

    glm::quat orientation();

    const OculusInfo& info() const;


protected:
    OVR::HMDDevice* m_hmdDevice;
    OVR::SensorDevice* m_sensorDevice;
    OVR::SensorFusion m_sensorFusion;

    std::unique_ptr<OculusInfo> m_info;
};

