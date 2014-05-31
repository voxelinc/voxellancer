#include "sectorloader.h"


SectorLoader::SectorLoader(const std::string& name, const std::string& prefix, Universe& universe):
    m_name(name),
    m_prefix(prefix),
    m_universe(universe),
    m_loadedSector(nullptr);
{
}

SectorLoader::~SectorLoader() = default;

LoadedSector* SectorLoader::load() {
    m_sector = std::make_shared<Sector>(m_name, m_universe);
    
    delete m_loadedSector;
    m_loadedSector = new LoadedSector(m_m_sector);

    loadSkybox();
    loadLight();
    loadJumpgates();

    return m_sector;
}

void SectorLoader::loadSkybox() {
    std::string skyboxDirectory = "data/textures/skybox/" + Property<std::string>::get(prefix + "." + name + ".general.skybox");
    Skybox* skybox = new Skybox(skyboxDirectory);

    m_sector->setSkybox(skybox);
}

void SectorLoader::loadLight() {
    m_sector->setLightDirection(Property<glm::vec3>::get(prefix + "." + name + ".general.lightdir"));
}

void SectorLoader::loadJumpgates() {
    for (int i = 0; PropertyManager::instance()->hasGroup(prefix + "." + name + ".general.jumpgate" + std::to_string(i); i++) {
        loadJumpgate(i);
    }
}

void SectorLoader::loadJumpgate(int index) {
    Jumpgate* jumpgate = WorldObjectBuilder("jumpgate").buildJumpgate();
    jumpgate->transform().setPosition();
}


