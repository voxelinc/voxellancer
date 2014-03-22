#include "mission.h"

#include "scripting/missionscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "ui/hud/hud.h"

#include "world/world.h"

#include "player.h"


Mission::Mission(const std::string& path):
    m_script(new MissionScript(*this, &World::instance()->scriptEngine())),
    m_active(true),
    m_succeeded(false)
{
    m_script->load(path);
    World::instance()->scriptEngine().addScript(m_script);
}

Mission::~Mission() = default;

void Mission::start() {
    World::instance()->player().hud().showMissionInfo(
        m_script->luaWrapper().call<std::string>("missionTitle"),
        m_script->luaWrapper().call<std::string>("missionCaption")
    );
}

bool Mission::active() const {
    return m_active;
}

bool Mission::succeeded() const {
    return m_succeeded;
}

void Mission::succeed() {
    assert(m_active);

    m_succeeded = true;
    m_script->onSuccess();

    over();
}

void Mission::fail() {
    assert(m_active);

    m_succeeded = true;
    m_script->onFailure();

    over();
}

void Mission::over() {
    m_active = false;
    World::instance()->scriptEngine().removeScript(m_script.get());
}

void Mission::update(float deltaSec) {

}

