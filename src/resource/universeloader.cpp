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
    connectSectors();

    return m_universe;
}

void UniverseLoader::loadSectors() {
    std::string sectorsPrefix(m_prefix + ".sectors");

    PropertyDirectory(m_path + "/sectors", sectorsPrefix).read();

    for (std::string& sector : PropertyManager::instance()->groups(sectorsPrefix)) {
        SectorLoader loader(sector, sectorsPrefix, *m_universe);
        std::shared_ptr<LoadedSector> loadedSector = loader.load();

        m_universe->addSector(loadedSector.sector());
        m_loadedSectors[sector] = loadedSector;
    }
}

void UniverseLoader::connectSectors() {
    for (auto& pair : m_loadedSectors) {
        std::shared_ptr<LoadedSector>& loadedSector = pair.second;

        for (std::shared_ptr<LoadedJumpgate>& loadedJumpgate : loadedSector.loadedJumpgates()) {
            std::shared_ptr<LoadedSector>& targetSector = m_loadedSectors[loadedJumpgate->targetSector()];
            if (!targetSector) {
                throw std::runtime_error("No such sector '" + loadedJumpgate->targetSector() + "'");           
            }
            
            glow::ref_ptr<Jumpgate> buddy = targetSector->jumpgate(loadedJumpgate->buddy());
            if (!buddy) {
                throw std::runtime_error("No such jumpgate '" + std::to_string(loadedJumpgate->buddy()) + "' in sector '" + loadedJumpgate->targetSector() + "'");
            }            

            loadedJumpgate->jumpgate()->setBuddy(buddy);
        }
    }
}

