#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/gameplayscript.h"
#include "scripting/scriptengine.h"

#include "universe/jumpgate.h"
#include "universe/universe.h"
#include "universe/sector.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectinfo.h"

#include "player.h"


BaseScenario::BaseScenario(Universe& universe) :
    m_universe(universe)
{
}

void BaseScenario::load() {
    glowutils::AutoTimer timer("Loading Scenario");

    createUniverse();
    populateUniverse();
    startScripts();
}

void BaseScenario::createUniverse() {
    auto backen = std::make_shared<Sector>("backen", m_universe);
    auto wlf = std::make_shared<Sector>("withlesserforce", m_universe);
    auto winterbreeze = std::make_shared<Sector>("winterbreeze", m_universe);

    m_universe.addSector(backen);
    m_universe.addSector(wlf);
    m_universe.addSector(winterbreeze);

    glow::ref_ptr<Jumpgate> backenJumpgate(WorldObjectBuilder("jumpgate").buildJumpgate());
    glow::ref_ptr<Jumpgate> winterbreezeJumpgate(WorldObjectBuilder("jumpgate").buildJumpgate());

    backenJumpgate->setBuddy(winterbreezeJumpgate);
    winterbreezeJumpgate->setBuddy(backenJumpgate);

    backenJumpgate->transform().setPosition(glm::vec3(-60, 0, -160));
    winterbreezeJumpgate->transform().setPosition(glm::vec3(-60, 0, -160));

    backenJumpgate->spawn(*backen);
    winterbreezeJumpgate->spawn(*winterbreeze);
}

void BaseScenario::populateUniverse() {
    Ship *playership = WorldObjectBuilder("pirateheavy").buildShip();
    playership->transform().setPosition(glm::vec3(0, 0, 0));
    playership->info().setName("metdelivery");

    Sector& sector = *m_universe.sector("backen");

    if (playership->canSpawn(sector)) {
        playership->spawn(sector);
        m_universe.player().setShip(playership);
    } else {
        glow::warning() << "Failed to spawn playership";
    }
}

void BaseScenario::startScripts() {
    GamePlayScript* demo = new GamePlayScript(m_universe.scriptEngine());
    demo->load("data/scripts/scenarios/demo.lua");
    demo->spawn(m_universe);
    demo->start();

    GamePlayScript* timertest = new GamePlayScript(m_universe.scriptEngine());
    timertest->load("data/scripts/scenarios/timertest.lua");
    timertest->spawn(m_universe);
    timertest->start();
}

