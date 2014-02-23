#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "property/property.h"


namespace OVR {
    class HMDInfo;
}

class StereoRenderInfo {
public:
    static StereoRenderInfo fromOVRInfo(const OVR::HMDInfo& hmdInfo);
    static StereoRenderInfo dummy();


    StereoRenderInfo();

    float hScreenSize() const;
    float vScreenSize() const;

    float vScreenCenter() const;

    float eyeToScreenDistance() const;

    float lensSeparationDistance() const;

    float interpupillaryDistance() const;

    int hResolution() const;
    int vResolution() const;

    float distortionK(int index) const;
    std::vector<float> distortionKs() const;

    float distortionScale() const;

    float fovy() const;

    glm::vec2 leftEyeLensCenter() const;
    glm::vec2 rightEyeLensCenter() const;

    glm::vec3 leftEyeOffset() const;
    glm::vec3 rightEyeOffset() const;

    glm::vec3 leftEyeProjectionOffset() const;
    glm::vec3 rightEyeProjectionOffset() const;


protected:
    float m_hScreenSize;
    float m_vScreenSize;
    float m_vScreenCenter;
    float m_eyeToScreenDistance;
    float m_lensSeparationDistance;
    float m_interpupillaryDistance;
    int m_hResolution;
    int m_vResolution;
    std::vector<float> m_distortionKs;
    float m_distortionScale;
    float m_fovy;
    Property<float> m_eyeZOffset;

    float projectionCenterOffset() const;
};

