#pragma once

#include <vector>

#include <OVR.h>

#include <glm/glm.hpp>


class StereoRenderInfo {
public:
    StereoRenderInfo(const OVR::HMDInfo& hmdInfo);

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
};

