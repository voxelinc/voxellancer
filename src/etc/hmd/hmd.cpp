#include "oculus.h"

#include <cassert>
#include <iostream>


HMD::HMD(OVR::HMDDevice* hmdDevice):
    m_hmdDevice(hmdDevice)
{
    m_sensorDevice = m_hmdDevice->GetSensor();
    assert(m_sensorDevice);

    if(m_sensorDevice) {
        m_sensorFusion.AttachToSensor(m_sensorDevice);
    }

    OVR::HMDInfo ovrInfo;
    m_hmdDevice->GetDeviceInfo(&ovrInfo);

    m_stereoRenderInfo = StereoRenderInfo::fromOVRInfo(ovrInfo);
}

HMD::~HMD() {
    m_sensorDevice->Release();
    m_hmdDevice->Release();
}

glm::quat HMD::orientation() {
    glm::vec3 euler;
    OVR::Quatf ovrOrientation = m_sensorFusion.GetOrientation();

    ovrOrientation.GetEulerAngles<OVR::Axis_X, OVR::Axis_Y, OVR::Axis_Z,g OVR::Rotate_CW, OVR::Handed_R>(&euler.x, &euler.y, &euler.z);

    euler.x *= -1.0f;
    euler.y *= -1.0f;

    return glm::quat(euler);
}

const StereoRenderInfo& HMD::info() const {
    return m_stereoRenderInfo;
}

