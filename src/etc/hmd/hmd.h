#pragma once

#include <memory>

#include <OVR.h>

#include <glow/ref_ptr.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "display/stereorenderinfo.h"

class HMD {
public:
    HMD(OVR::HMDDevice* hmdDevice);
    ~HMD();

    glm::quat orientation();

    const StereoRenderInfo& stereoRenderInfo() const;


protected:
    OVR::HMDDevice* m_hmdDevice;
    OVR::SensorDevice* m_sensorDevice;
    OVR::SensorFusion m_sensorFusion;

    StereoRenderInfo m_stereoRenderInfo;
};

