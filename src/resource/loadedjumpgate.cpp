#include "loadedjumpgate.h"


LoadedJumpgate::LoadedJumpgate(glow::ref_ptr<Jumpgate>& jumpgate, const std::string& targetSector, int buddy):
    m_jumpgate(jumpgate),
    m_targetSector(targetSector),
    m_buddy(buddy)
{
}

LoadedJumpgate::~LoadedJumpgate() = default;

glow::ref_ptr<Jumpgate>& LoadedJumpgate::jumpgate() {
    return m_jumpgate;
}

const std::string& LoadedJumpgate::targetSector() {
    return m_targetSector;
}

int LoadedJumpgate::buddy() {
    return m_buddy;
}


