#include "rocket.h"

#include "ai/aitask.h"
#include "ai/basictasks/directsuicidetask.h"

#include "collision/collisionfilter.h"

#include "equipment/engineslot.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxeleffect/explosion.h"

#include "worldobject/worldobjectcomponents.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket():
    Projectile(),
    m_boardComputer(this),
    m_aiTask(nullptr)
{
    collisionFilter().setCollideableWith(WorldObjectType::Rocket, false);
}

WorldObjectType Rocket::objectType() const {
    return WorldObjectType::Rocket;
}

WorldObject* Rocket::target() {
    return m_targetHandle.get();
}

void Rocket::setTarget(WorldObject* targetObject) {
    if (targetObject) {
        m_targetHandle = makeHandle(targetObject);
        m_aiTask.reset(new DirectSuicideTask(&m_boardComputer, targetObject));
    } else {
        m_targetHandle = Handle<WorldObject>();
        m_aiTask.reset(nullptr);
    }
}

void Rocket::update(float deltaSec) {
    Projectile::update(deltaSec);

    if (m_aiTask) {
        m_aiTask->update(deltaSec);
        m_boardComputer.update(deltaSec);
    } else {
        components().setEngineState(EngineState(
            glm::vec3(0, 0, -1),
            glm::vec3(0, 0, 0)
            ));
    }
}

void Rocket::onLifetimeOver() {
    if(explosion()) {
        explosion()->spawn(transform().position());
    }
}

