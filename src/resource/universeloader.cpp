#include "universeloader.h"

#include <iostream>

#include "property/property.h"
#include "property/propertydirectory.h"
#include "property/propertymanager.h"

#include "universe/universe.h"


UniverseLoader::UniverseLoader(const std::string& path):
    m_path(path),
    m_universe(nullptr)
{
    m_prefix = "universe";
}

UniverseLoader::~UniverseLoader() = default;

Universe* UniverseLoader::load() {
    delete m_universe;
    m_universe = new Universe();

    loadSectors();

    return m_universe;
}

void UniverseLoader::loadSectors() {
    std::string sectorsPrefix(m_prefix + ".sectors");

    PropertyDirectory(m_path + "/sectors", sectorsPrefix).read();

    for (std::string group : PropertyManager::instance()->groups(sectorsPrefix)) {
        std::shared_ptr<Sector> sector = SectorLoader(group, sectorsPrefix, *m_universe).load();
        m_universe->addSector(sector);
    }
}

