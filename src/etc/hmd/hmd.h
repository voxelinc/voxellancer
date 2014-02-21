#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/ref_ptr.h>

#include "display/stereorenderinfo.h"


namespace OVR {
    class HMDDevice;
    class SensorDevice;
    class SensorFusion;
}

class HMD {
public:
    HMD(OVR::HMDDevice* hmdDevice);
    ~HMD();

    glm::quat orientation();

    const StereoRenderInfo& stereoRenderInfo() const;


protected:
    std::unique_ptr<OVR::SensorFusion> m_sensorFusion;
    OVR::HMDDevice* m_hmdDevice;
    OVR::SensorDevice* m_sensorDevice;

    StereoRenderInfo m_stereoRenderInfo;
};

