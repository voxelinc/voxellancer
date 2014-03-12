#include "commonbindings.h"


#include "events/eventpoller.h"
#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/scriptengine.h"

#include "world/world.h"
#include "worldobject/worldobject.h"


CommonBindings::CommonBindings(GamePlayScript& script): 
    Bindings(script) 
{

}


void CommonBindings::initialize() {
    m_lua.Register("valid", this, &CommonBindings::apiIsKeyValid);
    m_lua.Register("showText", this, &CommonBindings::apiShowText);
    m_lua.Register("showTextFor", this, &CommonBindings::apiShowTextFor);

    m_lua.Register("setActive", this, &CommonBindings::apiSetEventActive);

    m_lua.Register("createSingleShotTimer", this, &CommonBindings::apiCreateSingleShotTimer);
    m_lua.Register("createLoopingTimer", this, &CommonBindings::apiCreateLoopingTimer);

    m_lua.Register("onAABBEntered", this, &CommonBindings::apiOnAABBEntered);
}


bool CommonBindings::apiIsKeyValid(apikey key) {
    return m_scriptEngine.get<void>(key) != nullptr;
}

int CommonBindings::apiShowText(const std::string& string) {
    return apiShowTextFor(string, 3);
}


int CommonBindings::apiShowTextFor(const std::string& string, int seconds) {
    // TODO show text on hud
    glow::debug("Script: %; [%;s]", string, seconds);
    return 0;
}


int CommonBindings::apiSetEventActive(apikey eventPoll, bool active) {
    EventPoll* poll = m_scriptEngine.get<EventPoll>(eventPoll);

    if (!poll) { return -1; }

    poll->setActive(active);
    return 0;
}

apikey CommonBindings::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<SingleShotTimer>(delta, [=] { m_lua.call(callback); });
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

apikey CommonBindings::apiCreateLoopingTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<LoopingTimer>(delta, [=] { m_lua.call(callback); });
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

apikey CommonBindings::apiOnAABBEntered(apikey key, const glm::vec3& llf, const glm::vec3& urb, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) { return -1; }

    auto enteredPoll = std::make_shared<AABBEnteredPoll>(worldObject, AABB(llf, urb), [=] { m_lua.call(callback, key); });
    World::instance()->eventPoller().addPoll(enteredPoll);
    return enteredPoll->scriptKey();
}

