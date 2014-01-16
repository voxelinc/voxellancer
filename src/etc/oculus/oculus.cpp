#include "oculus.h"

#include <cassert>
#include <iostream>


Oculus::Oculus(OVR::HMDDevice* hmdDevice):
    m_hmdDevice(hmdDevice)
{
    m_sensorDevice = m_hmdDevice->GetSensor();
    assert(m_sensorDevice);

    if(m_sensorDevice) {
        m_sensorFusion.AttachToSensor(m_sensorDevice);
    }
}

glm::quat Oculus::orientation() {
    glm::vec3 euler;
    OVR::Quatf ovrOrientation = m_sensorFusion.GetOrientation();

    ovrOrientation.GetEulerAngles<OVR::Axis_X, OVR::Axis_Y, OVR::Axis_Z, OVR::Rotate_CW, OVR::Handed_R>(&euler.x, &euler.y, &euler.z);

    euler.x *= -1.0f;
    euler.y *= -1.0f;

    return glm::quat(euler);
}
