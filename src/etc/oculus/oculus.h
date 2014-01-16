#pragma once

#include <OVR.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class Oculus {
public:
    Oculus(OVR::HMDDevice* hmdDevice);

    glm::quat orientation();


protected:
    OVR::HMDDevice* m_hmdDevice;
    OVR::SensorDevice* m_sensorDevice;
    OVR::SensorFusion m_sensorFusion;
};

