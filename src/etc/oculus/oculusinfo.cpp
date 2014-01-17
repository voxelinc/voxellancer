#include "oculusinfo.h"

#include <cassert>


OculusInfo::OculusInfo(const OVR::HMDInfo& hmdInfo):
    m_hScreenSize(hmdInfo.HScreenSize),
    m_vScreenSize(hmdInfo.VScreenSize),
    m_vScreenCenter(hmdInfo.VScreenCenter),
    m_eyeToScreenDistance(hmdInfo.EyeToScreenDistance),
    m_lensSeparationDistance(hmdInfo.LensSeparationDistance),
    m_interpupillaryDistance(hmdInfo.InterpupillaryDistance),
    m_hResolution(hmdInfo.HResolution),
    m_vResolution(hmdInfo.VResolution)
{
    m_distortionKs = std::vector<float>{
        hmdInfo.DistortionK[0],
        hmdInfo.DistortionK[1],
        hmdInfo.DistortionK[2],
        hmdInfo.DistortionK[3]
    };
}

float OculusInfo::hScreenSize() const {
    return m_hScreenSize;
}

float OculusInfo::vScreenSize() const {
    return m_vScreenSize;
}

float OculusInfo::vScreenCenter() const {
    return m_vScreenCenter;
}

float OculusInfo::eyeToScreenDistance() const {
    return m_eyeToScreenDistance;
}

float OculusInfo::lensSeparationDistance() const {
    return m_lensSeparationDistance;
}

float OculusInfo::interpupillaryDistance() const {
    return m_interpupillaryDistance;
}

int OculusInfo::hResolution() const {
    return m_hResolution;
}

int OculusInfo::vResolution() const {
    return m_vResolution;
}

float OculusInfo::distortionK(int index) const {
    assert(index >= 0 && index < 4);
    return m_distortionKs[index];
}

std::vector<float> OculusInfo::distortionKs() const {
    return m_distortionKs;
}
