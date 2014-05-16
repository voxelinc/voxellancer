#include "mission.h"

#include "scripting/missionscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "ui/hud/hud.h"

#include "world/world.h"

#include "player.h"


Mission::Mission(const std::string& path):
    m_scriptPath(path),
    m_state(MissionState::Idle)
{
}

Mission::~Mission() = default;

void Mission::start() {
    assert(universe());

    m_state = MissionState::Running;
    universe()->player().hud().showMissionInfo(
        m_script->luaWrapper().call<std::string>("missionTitle"),
        m_script->luaWrapper().call<std::string>("missionCaption")
    );
}

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

}

void Mission::spawn() {
    assert(universe());

    m_script.reset(new MissionScript(*this, universe()->scriptEngine()));
    m_script->load(m_scriptPath);
    universe()->scriptEngine().addScript(m_script);

    universe()->addFunctionalElement(this);
}

void Mission::over() {
    m_script->stop();

    assert(world());
    world()->removeElement(this);
}

