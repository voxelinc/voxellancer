#include "universeloader.h"

#include <iostream>

#include "property/property.h"
#include "property/propertydirectory.h"
#include "property/propertymanager.h"

#include "universe/universe.h"

#include "jumpgateloader.h"
#include "sectorloader.h"


UniverseLoader::UniverseLoader(const std::string& path):
    m_path(path),
    m_universe(nullptr),
    m_loaded(false)
{
    m_prefix = "universe";
}

UniverseLoader::~UniverseLoader() = default;

Universe* UniverseLoader::universe() {
    lazyLoad();
    return m_universe;
}

void UniverseLoader::lazyLoad() {
    if (m_loaded) {
        return;
    }

    m_universe = new Universe();

    loadSectors();
    connectJumpgates();

    m_loaded = true;
}

void UniverseLoader::loadSectors() {
    std::string sectorsPrefix(m_prefix + ".sectors");
    PropertyDirectory(m_path + "/sectors", sectorsPrefix).read();

    for (std::string& sector : PropertyManager::instance()->groups(sectorsPrefix)) {
        SectorLoader* loader = new SectorLoader(sector, sectorsPrefix, *m_universe);

        m_universe->addSector(loader->sector());
        m_sectorLoaders[sector].reset(loader);
    }
}

void UniverseLoader::connectJumpgates() {
    for (auto& pair : m_sectorLoaders) {
        SectorLoader* sectorLoader = pair.second.get();

        sectorLoader->foreachJumpgateLoader([&] (JumpgateLoader* jumpgateLoader) {
            SectorLoader* targetSectorLoader = m_sectorLoaders[jumpgateLoader->targetSector()].get();
            if (!targetSectorLoader) {
                throw std::runtime_error("No such sector '" + jumpgateLoader->targetSector() + "'");
            }

            glow::ref_ptr<Jumpgate> buddy = targetSectorLoader->jumpgate(jumpgateLoader->buddy());
            if (!buddy) {
                throw std::runtime_error("No such jumpgate '" + std::to_string(jumpgateLoader->buddy()) + "' in sector '" + jumpgateLoader->targetSector() + "'");
            }

            jumpgateLoader->jumpgate()->setBuddy(buddy);
        });
    }
}

