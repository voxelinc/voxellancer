#include "commonbindings.h"

#include "events/eventpoller.h"
#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/gameplayscript.h"
#include "scripting/scriptcallback.h"
#include "scripting/scriptengine.h"

#include "world/world.h"
#include "worldobject/worldobject.h"

#include "sound/soundmanager.h"
#include "sound/sound.h"


CommonBindings::CommonBindings(GamePlayScript& script):
    Bindings(script)
{

}


void CommonBindings::initialize() {
    m_lua.Register("valid", this, &CommonBindings::apiIsKeyValid);
    m_lua.Register("showText", this, &CommonBindings::apiShowText);
    m_lua.Register("showTextFor", this, &CommonBindings::apiShowTextFor);
    m_lua.Register("playVoice", this, &CommonBindings::apiPlayVoice);
    m_lua.Register("setActive", this, &CommonBindings::apiSetEventActive);

    m_lua.Register("createSingleShotTimer", this, &CommonBindings::apiCreateSingleShotTimer);
    m_lua.Register("createLoopingTimer", this, &CommonBindings::apiCreateLoopingTimer);

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

int CommonBindings::apiPlayVoice(const std::string& soundFile) {
    std::shared_ptr<Sound> sound = SoundManager::current()->play(soundFile, glm::vec3(0, 0, -1), true);
    return sound->status() == Sound::Status::Null ? -1 : 0;
}

int CommonBindings::apiSetEventActive(apikey eventPoll, bool active) {
    EventPoll* poll = m_scriptEngine.get<EventPoll>(eventPoll);

    if (!poll) { return -1; }

    poll->setActive(active);
    return 0;
}

apikey CommonBindings::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<SingleShotTimer>(delta, createCallback(callback));
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

apikey CommonBindings::apiCreateLoopingTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<LoopingTimer>(delta, createCallback(callback));
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

