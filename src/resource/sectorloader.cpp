#include "sectorloader.h"


SectorLoader::SectorLoader(const std::string& name, const std::string& prefix, Universe& universe):
    m_name(name),
    m_prefix(prefix),
    m_universe(universe)
{
}

SectorLoader::~SectorLoader() = default;

std::shared_ptr<Sector>& SectorLoader::load() {
    m_sector = std::make_shared<Sector>(m_name, m_universe);



    return m_sector;
}

