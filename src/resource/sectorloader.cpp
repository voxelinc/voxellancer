#include "sectorloader.h"

#include <memory>

#include "display/rendering/skybox.h"

#include "property/property.h"

#include "universe/jumpgate.h"
#include "universe/sector.h"

#include "jumpgateloader.h"


SectorLoader::SectorLoader(const std::string& name, const std::string& prefix, Universe& universe):
    m_name(name),
    m_prefix(prefix),
    m_universe(universe),
    m_loaded(false)
{
}

SectorLoader::~SectorLoader() = default;

std::shared_ptr<Sector> SectorLoader::sector() {
    lazyLoad();
    return m_sector;
}

Jumpgate* SectorLoader::jumpgate(int index) {
    assert(index < m_jumpgateLoaders.size() && index >= 0);
    return m_jumpgateLoaders[index]->jumpgate();
}

void SectorLoader::foreachJumpgateLoader(const std::function<void(JumpgateLoader*)> function) {
    lazyLoad();

    for (auto& jumpgateLoader : m_jumpgateLoaders) {
        function(jumpgateLoader.get());
    }
}

void SectorLoader::lazyLoad() {
    if (m_loaded) {
        return;
    }

    m_sector = std::make_shared<Sector>(m_name, m_universe);

    loadSkybox();
    loadLight();
    loadJumpgates();

    m_loaded = true;
}

void SectorLoader::loadSkybox() {
    std::string skyboxDirectory = "data/textures/skybox/" + Property<std::string>::get(m_prefix + "." + m_name + ".general.skybox");
    Skybox* skybox = new Skybox(skyboxDirectory);

    m_sector->setSkybox(skybox);
}

void SectorLoader::loadLight() {
    m_sector->setLightDirection(Property<glm::vec3>::get(m_prefix + "." + m_name + ".general.lightdir"));
}

void SectorLoader::loadJumpgates() {
    for (int i = 0; PropertyManager::instance()->hasGroup(m_prefix + "." + m_name + ".jumpgate" + std::to_string(i)); i++) {
        loadJumpgate(i);
    }
}

void SectorLoader::loadJumpgate(int index) {
    JumpgateLoader* jumpgateLoader = new JumpgateLoader(m_prefix + "." + m_name + ".jumpgate" + std::to_string(index));

    jumpgateLoader->jumpgate()->spawn(*m_sector);

    m_jumpgateLoaders.push_back(std::unique_ptr<JumpgateLoader>(jumpgateLoader));
}

