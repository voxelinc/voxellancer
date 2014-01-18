#pragma once

#include <vector>

#include "programs/blitprogram.h"


class StereoBlitProgram: public BlitProgram {
public:
    StereoBlitProgram();

    void setDistortionKs(std::vector<float> distortionKs);
    void setDistortionScale(float distortionScale);
    void setLensCenter(float lensCenter);

    virtual void blit() override;


protected:
    std::vector<float> m_distortionKs;
    float m_distortionScale;
    float m_lensCenter;
};

