#pragma once

#include <vector>

#include "programs/blitprogram.h"


class StereoBlitProgram: public BlitProgram {
public:
    StereoBlitProgram();

    void setDistortionKs(std::vector<float> distortionKs);

    virtual void blit() override;


protected:
    std::vector<float> m_distortionKs;
};

