#include "mission.h"

#include "scripting/missionscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "ui/hud/hud.h"

#include "universe/universe.h"

#include "player.h"


Mission::Mission(const std::string& path):
    m_scriptPath(path),
    m_state(MissionState::Idle)
{
}

Mission::~Mission() = default;

MissionState Mission::state() const {
    return m_state;
}

void Mission::succeed() {
    assert(m_state == MissionState::Running);

    m_state = MissionState::Succeeded;
    m_script->onSuccess();

    over();
}

void Mission::fail() {
    assert(m_state == MissionState::Running);

    m_state = MissionState::Failed;
    m_script->onFailure();

    over();
}

void Mission::update(float deltaSec) {
    m_script->update(deltaSec);
}

void Mission::doSpawn() {
    assert(universe());

    m_script = new MissionScript(*this, universe()->scriptEngine());
    m_script->load(m_scriptPath);
    m_script->start();

    universe()->addFunctionalObject(this);

    m_state = MissionState::Running;

    universe()->player().hud().showMissionInfo(
        m_script->luaWrapper().call<std::string>("missionTitle"),
        m_script->luaWrapper().call<std::string>("missionCaption")
    );
}

void Mission::over() {
    scheduleRemoval();
}



