#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/scriptengine.h"

#include "universe/universe.h"
#include "universe/sector.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectinfo.h"

#include "player.h"


BaseScenario::BaseScenario(Universe* universe) :
    m_universe(universe)
{
}

void BaseScenario::load() {
    glowutils::AutoTimer timer("Loading Scenario");

    createUniverse();
    populateUniverse();
}

void BaseScenario::createUniverse() {
    auto backen = std::make_shared<Sector>("backen", *m_universe);
    auto wlf = std::make_shared<Sector>("withlesserforce", *m_universe);
    auto winterbreeze = std::make_shared<Sector>("winterbreeze", *m_universe);

    m_universe->addSector(backen);
    m_universe->addSector(wlf);
    m_universe->addSector(winterbreeze);
}

void BaseScenario::populateUniverse() {
    Ship *playership = WorldObjectBuilder("pirateheavy").buildShip();
    playership->transform().setPosition(glm::vec3(0, 0, 10));
    playership->info().setName("metdelivery");
    playership->spawn(m_universe->sector("backen"));

    m_universe->player().setShip(playership);
}


