#include "mission.h"

#include "scripting/missionscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "ui/hud/hud.h"

#include "world/world.h"

#include "player.h"


Mission::Mission(const std::string& path):
    m_script(new MissionScript(*this, World::instance()->scriptEngine())),
    m_state(MissionState::Idle)
{
    m_script->load(path);
    World::instance()->scriptEngine().addScript(m_script);
}

Mission::~Mission() = default;

void Mission::start() {
    m_state = MissionState::Running;
    World::instance()->player().hud().showMissionInfo(
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

void Mission::over() {
    m_script->stop();

    assert(world());
    world()->removeElement(this);
}

