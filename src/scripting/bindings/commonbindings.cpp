#include "commonbindings.h"

#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/gameplayscript.h"
#include "scripting/scriptcallback.h"
#include "scripting/scriptengine.h"

#include "sound/soundmanager.h"
#include "sound/sound.h"

#include "ui/hud/hud.h"

#include "universe/universe.h"

#include "worldobject/worldobject.h"

#include "player.h"


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
    m_script.universe()->player().hud().showMissionMessage(message);

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
    auto timer = new SingleShotTimer(delta, createCallback(callback));
    timer->spawn(m_script.universe());

    return timer->scriptKey();
}

apikey CommonBindings::apiCreateLoopingTimer(const std::string& callback, float delta) {
    auto timer = new LoopingTimer(delta, createCallback(callback));
    timer->spawn(m_script.universe());

    return timer->scriptKey();
}

