#include "stereorenderinfo.h"

#include <cassert>
#include <iostream>

#include <OVR.h>

#include "geometry/size.h"
#include "geometry/viewport.h"

#include "etc/contextprovider.h"

#include "utils/metrics.h"


StereoRenderInfo StereoRenderInfo::fromOVRInfo(const OVR::HMDInfo& hmdInfo) {
    StereoRenderInfo result;

    result.m_hScreenSize = hmdInfo.HScreenSize;
    result.m_vScreenSize = hmdInfo.VScreenSize;
    result.m_vScreenCenter = hmdInfo.VScreenCenter;
    result.m_eyeToScreenDistance = hmdInfo.EyeToScreenDistance;
    result.m_lensSeparationDistance = hmdInfo.LensSeparationDistance;
    result.m_interpupillaryDistance = hmdInfo.InterpupillaryDistance;
    result.m_hResolution = hmdInfo.HResolution;
    result.m_vResolution = hmdInfo.VResolution;

    result.m_distortionKs = std::vector<float>{
        hmdInfo.DistortionK[0],
        hmdInfo.DistortionK[1],
        hmdInfo.DistortionK[2],
        hmdInfo.DistortionK[3]
    };

    OVR::Util::Render::StereoConfig stereoConfig;

    Size<int> resolution(ContextProvider::instance()->resolution());

    stereoConfig.SetFullViewport(OVR::Util::Render::Viewport(0, 0, resolution.width(), resolution.height()));
    stereoConfig.SetHMDInfo(hmdInfo);
    stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_LeftRight_Multipass);
    stereoConfig.SetDistortionFitPointVP(-1.0f, 0.0f);

    result.m_distortionScale = stereoConfig.GetDistortionScale();
    result.m_fovy = glm::radians(stereoConfig.GetYFOVDegrees());

    return result;
}

StereoRenderInfo StereoRenderInfo::dummy() {
    StereoRenderInfo result;

    Size<int> resolution(ContextProvider::instance()->resolution());

    result.m_hScreenSize = 0.15f;
    result.m_vScreenSize = 0.06f;
    result.m_vScreenCenter = result.m_vScreenSize / 2.0f;
    result.m_eyeToScreenDistance = 0.04f;
    result.m_lensSeparationDistance = 0.05f;
    result.m_interpupillaryDistance = 0.064f;
    result.m_hResolution = resolution.width();
    result.m_vResolution = resolution.height();

    result.m_distortionKs = std::vector<float>{
        0.6f,
        0.5f,
        0.2f,
        0.1f
    };

    result.m_distortionScale = 1.5;
    result.m_fovy = glm::radians(120.0f);

    return result;
}

StereoRenderInfo::StereoRenderInfo():
    m_hScreenSize(0.0f),
    m_vScreenSize(0.0f),
    m_vScreenCenter(0.0f),
    m_eyeToScreenDistance(0.0f),
    m_lensSeparationDistance(0.0f),
    m_interpupillaryDistance(0.0f),
    m_hResolution(0),
    m_vResolution(0),
    m_distortionScale(0.0f),
    m_fovy(0.0f),
    m_eyeZOffset("vr.eyeZOffset")
{

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

glm::vec2 StereoRenderInfo::leftEyeLensCenter() const {
    return glm::vec2(1 - 2 * m_lensSeparationDistance / m_hScreenSize, 0.0f);
}

glm::vec2 StereoRenderInfo::rightEyeLensCenter() const {
    return glm::vec2(-(1 - 2 * m_lensSeparationDistance / m_hScreenSize), 0.0f);
}

glm::vec3 StereoRenderInfo::leftEyeOffset() const {
    return glm::vec3(Metrics::instance()->toGameUnits(-m_interpupillaryDistance / 2.0f), 0.0f, Metrics::instance()->toGameUnits(m_eyeZOffset.get()));
}

glm::vec3 StereoRenderInfo::rightEyeOffset() const {
    return glm::vec3(Metrics::instance()->toGameUnits(m_interpupillaryDistance / 2.0f), 0.0f, Metrics::instance()->toGameUnits(m_eyeZOffset.get()));
}

glm::vec3 StereoRenderInfo::leftEyeProjectionOffset() const {
    return glm::vec3(projectionCenterOffset(), 0.0f, 0.0f);
}

glm::vec3 StereoRenderInfo::rightEyeProjectionOffset() const {
    return glm::vec3(-projectionCenterOffset(), 0.0f, 0.0f);
}

float StereoRenderInfo::projectionCenterOffset() const {
    float viewCenter = m_hScreenSize * 0.25f;
    float eyeProjectionShift = viewCenter - m_lensSeparationDistance * 0.5f;
    return 4.0f * eyeProjectionShift / m_hScreenSize;
}

