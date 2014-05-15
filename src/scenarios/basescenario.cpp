#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/scriptengine.h"

#include "world/universe.h"
#include "world/sector.h"


BaseScenario::BaseScenario(Universe* universe) :
    m_universe(universe)
{
}

void BaseScenario::load() {
    glowutils::AutoTimer timer("Loading Scenario");

    createUniverse();
    populateUniverse();

    m_universe->scriptEngine().start();
}

void BaseScenario::createUniverse() {
    Sector* backen = new Sector("backen", m_universe);
    Sector* wlf = new Sector("withlesserforce", m_universe);
    Sector* winterbreeze = new Sector("winterbreeze", m_universe);

    m_universe->addSector(backen);
    m_universe->addSector(wlf);
    m_universe->addSector(winterbreezeS);
}

void BaseScenario::populateUniverse() {
    Ship *playership = WorldObjectBuilder("pirateheavy").buildShip();
    playership->setUniverse(universe);
    playership->setSector(universe->sector("backen"))
    playership->transform().setPosition(glm::vec3(0, 0, 10));
    playership->info().setName("metdelivery");
    playership->spawn();

    m_universe->player().setShip(testCluster);
}


