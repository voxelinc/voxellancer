#pragma once

#include "programs/blitprogram.h"


class MonoBlitProgram: public BlitProgram {
public:
    MonoBlitProgram();


protected:
    virtual void initializeShaders() override;
};

