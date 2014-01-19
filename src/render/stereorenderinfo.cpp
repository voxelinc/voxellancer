#include "oculusinfo.h"

#include <cassert>
#include <iostream>

#include "geometry/size.h"
#include "geometry/viewport.h"

#include "etc/windowmanager.h"


StereoRenderInfo::StereoRenderInfo(const OVR::HMDInfo& hmdInfo):
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

float StereoRenderInfo::hScreenSize() const {
    return m_hScreenSize;
}

float StereoRenderInfo::vScreenSize() const {
    return m_vScreenSize;
}

float StereoRenderInfo::vScreenCenter() const {
    return m_vScreenCenter;
}

float StereoRenderInfo::eyeToScreenDistance() const {
    return m_eyeToScreenDistance;
}

float StereoRenderInfo::lensSeparationDistance() const {
    return m_lensSeparationDistance;
}

float StereoRenderInfo::interpupillaryDistance() const {
    return m_interpupillaryDistance;
}

int StereoRenderInfo::hResolution() const {
    return m_hResolution;
}

int StereoRenderInfo::vResolution() const {
    return m_vResolution;
}

float StereoRenderInfo::distortionK(int index) const {
    assert(index >= 0 && index < 4);
    return m_distortionKs[index];
}

std::vector<float> StereoRenderInfo::distortionKs() const {
    return m_distortionKs;
}

float StereoRenderInfo::distortionScale() const {
    return m_distortionScale;
}

float StereoRenderInfo::fovy() const {
    return m_fovy;
}

float StereoRenderInfo::lensCenter() const {
    return 1 - 2 * m_lensSeparationDistance / m_hScreenSize;
}

