#include "oculusinfo.h"

#include <cassert>
#include <iostream>

#include "geometry/size.h"
#include "geometry/viewport.h"

#include "etc/windowmanager.h"


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

    OVR::Util::Render::StereoConfig stereoConfig;

    Size<int> resolution(WindowManager::instance()->resolution());

    stereoConfig.SetFullViewport(OVR::Util::Render::Viewport(0, 0, resolution.width(), resolution.height()));
    stereoConfig.SetHMDInfo(hmdInfo);
    stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_LeftRight_Multipass);
    stereoConfig.SetDistortionFitPointVP(-1.0f, 0.0f);

    m_distortionScale = stereoConfig.GetDistortionScale();
    m_fovy = stereoConfig.GetYFOVDegrees();
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

float OculusInfo::distortionScale() const {
    return m_distortionScale;
}

float OculusInfo::fovy() const {
    return m_fovy;
}

float OculusInfo::lensCenter() const {
    return 1 - 2 * m_lensSeparationDistance / m_hScreenSize;
}

