#include "aibindings.h"

#include "ai/basictasks/flytotask.h"
#include "ai/character.h"

#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "worldobject/ship.h"

AiBindings::AiBindings(GamePlayScript& script): 
    Bindings(script)
{

}

void AiBindings::initialize() {
    m_lua.Register("createFlyToTask", this, &AiBindings::apiCreateFlyToTask);
    m_lua.Register("setTargetPoint", this, &AiBindings::apiSetTargetPoint);

}

int AiBindings::apiCreateFlyToTask(int key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        return -1;
    }

    FlyToTask* flyToTask = new FlyToTask(ship->boardComputer());

    m_scriptEngine.registerScriptable(flyToTask);

    Character* character = ship->character();
    if (!character) {
        glow::warning("GamePlayScript: Ship '%;' has no Character", key);
        return -1;
    }
    character->setTask(std::shared_ptr<AiTask>(flyToTask));

    return flyToTask->scriptKey();
}

int AiBindings::apiSetTargetPoint(int key, float x, float y, float z) {
    FlyToTask* flyToTask = m_scriptEngine.get<FlyToTask>(key);

    if (!flyToTask) {
        return -1;
    }

    flyToTask->setTargetPoint(glm::vec3(x, y, z));
    return 0;
}
