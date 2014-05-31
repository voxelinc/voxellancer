#include "loadedsector.h"


LoadedSector::LoadedSector(std::shared_ptr<Sector>& sector):
    m_sector(sector)
{
}

LoadedSector::~LoadedSector() = default;

void LoadedSector::addJumpgate(LoadedJumpgate& jumpgate) {
    m_loadedJumpgates.push_back(jumpgate);
}

glow::ref_ptr<Jumpgate> LoadedSector::jumpgate(int index) {
    if (index < 0 || index >= m_loadedJumpgates.size()) {
        return glow::ref_ptr<Jumpgate>();
    }
    return m_loadedJumpgates[index]->jumpgate();
}

const std::vector<std::unique_ptr<LoadedJumpgate>>& LoadedSector::loadedJumpgates() {
    return m_loadedJumpgates;
}
