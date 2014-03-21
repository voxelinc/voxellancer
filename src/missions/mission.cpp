#include "mission.h"

#include "scripting/missionscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "ui/hud/hud.h"

#include "world/world.h"

#include "player.h"


Mission::Mission(const std::string& path):
    m_script(new MissionScript(*this, &World::instance()->scriptEngine())),
    m_active(true)
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

void Mission::succeeded() {
    m_active = false;
    m_script->onSuccess();
}

void Mission::failed() {
    m_active = false;
    m_script->onFailure();
}

void Mission::update(float deltaSec) {

}

