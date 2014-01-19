#pragma once

#include <memory>

#include <OVR.h>

#include <glow/ref_ptr.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "oculusinfo.h"


class HMD {
public:
    HMD(OVR::HMDDevice* hmdDevice);
    ~HMD();

    glm::quat orientation();

    const StereoRenderInfo& info() const;


protected:
    OVR::HMDDevice* m_hmdDevice;
    OVR::SensorDevice* m_sensorDevice;
    OVR::SensorFusion m_sensorFusion;

    std::unique_ptr<StereoRenderInfo> m_info;
};

