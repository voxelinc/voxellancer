#include "commonbindings.h"

#include "events/eventpoller.h"
#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/gameplayscript.h"
#include "scripting/scriptengine.h"

#include "world/world.h"
#include "worldobject/worldobject.h"


CommonBindings::CommonBindings(GamePlayScript& script):
    Bindings(script)
{
}

void CommonBindings::bind() {
    m_lua.Register("valid", this, &CommonBindings::apiValid);
    m_lua.Register("showText", this, &CommonBindings::apiShowText);
    m_lua.Register("showTextFor", this, &CommonBindings::apiShowTextFor);

    m_lua.Register("setActive", this, &CommonBindings::apiSetEventActive);

    m_lua.Register("createSingleShotTimer", this, &CommonBindings::apiCreateSingleShotTimer);
    m_lua.Register("createLoopingTimer", this, &CommonBindings::apiCreateLoopingTimer);

}

bool CommonBindings::apiValid(apikey key) {
    return m_scriptEngine.keyValid(key);
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

    if (!poll) {
        return -1;
    }

    poll->setActive(active);
    return 0;
}

apikey CommonBindings::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    SingleShotTimer* timer = new SingleShotTimer(delta, [=] { m_lua.call(callback); });

    World::instance()->eventPoller().addPoll(timer);
    m_script.addLocal(timer->scriptKey());

    return timer->scriptKey();
}

apikey CommonBindings::apiCreateLoopingTimer(const std::string& callback, float delta) {
    LoopingTimer* timer = new LoopingTimer(delta, [=] { m_lua.call(callback); });

    World::instance()->eventPoller().addPoll(timer);
    m_script.addLocal(timer->scriptKey());

    return timer->scriptKey();
}

