#pragma once

#include "universe/jumpgate.h"


class LoadedJumpgate {
public:
    LoadedJumpgate(glow::ref_ptr<Jumpgate>& jumpgate, const std::string& targetSector, int buddy);
    virtual ~LoadedJumpgate();

    glow::ref_ptr<Jumpgate>& jumpgate();
    const std::string& targetSector();
    int buddy();


protected:
    glow::ref_ptr<Jumpgate> m_jumpgate;
    std::string m_targetSector;
    int m_buddy;
};
