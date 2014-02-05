#include "hmd.h"

#include <cassert>
#include <iostream>


HMD::HMD(OVR::HMDDevice* hmdDevice):
    m_hmdDevice(hmdDevice)
{
    m_sensorDevice = m_hmdDevice->GetSensor();

    if(m_sensorDevice) {
        m_sensorFusion.AttachToSensor(m_sensorDevice);
    }

    OVR::HMDInfo ovrInfo;
    m_hmdDevice->GetDeviceInfo(&ovrInfo);

    m_stereoRenderInfo = StereoRenderInfo::fromOVRInfo(ovrInfo);
}

HMD::~HMD() {
    if (m_sensorDevice) {
        m_sensorDevice->Release();
    }
    if (m_hmdDevice) {
        m_hmdDevice->Release();
    }
}

glm::quat HMD::orientation() {
    OVR::Quatf ovrOrientation = m_sensorFusion.GetOrientation();
    
    return glm::quat(ovrOrientation.w, ovrOrientation.x, ovrOrientation.y, ovrOrientation.z);
}

const StereoRenderInfo& HMD::stereoRenderInfo() const {
    return m_stereoRenderInfo;
}

