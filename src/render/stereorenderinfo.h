#pragma once

#include <vector>

#include <OVR.h>

#include <glm/glm.hpp>


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

    float lensCenter() const;

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

    float StereoRenderInfo::projectionCenterOffset();
};

