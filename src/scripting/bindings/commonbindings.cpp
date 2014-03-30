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

#include "sound/soundmanager.h"
#include "sound/sound.h"

#include "player.h"
#include "ui/hud/hud.h"


CommonBindings::CommonBindings(GamePlayScript& script):
    Bindings(script)
{
}

void CommonBindings::bind() {
    m_lua.Register("valid", this, &CommonBindings::apiValid);
    m_lua.Register("showMessage", this, &CommonBindings::apiShowMessage);
    m_lua.Register("playVoice", this, &CommonBindings::apiPlayVoice);
    m_lua.Register("setActive", this, &CommonBindings::apiSetEventActive);

    m_lua.Register("createSingleShotTimer", this, &CommonBindings::apiCreateSingleShotTimer);
    m_lua.Register("createLoopingTimer", this, &CommonBindings::apiCreateLoopingTimer);

}

bool CommonBindings::apiValid(apikey key) {
    return m_scriptEngine.keyValid(key);
}

int CommonBindings::apiShowMessage(const std::string& message) {
    World::instance()->player().hud().showMissionMessage(message);
    return 0;
}


int CommonBindings::apiPlayVoice(const std::string& soundFile) {
    std::shared_ptr<Sound> sound = SoundManager::current()->play(soundFile, glm::vec3(0, 0, -1), true);
    return sound->status() == Sound::Status::Null ? -1 : 0;
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

