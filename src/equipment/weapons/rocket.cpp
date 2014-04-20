#include "rocket.h"

#include "ai/aitask.h"
#include "ai/basictasks/directsuicidetask.h"

#include "collision/collisionfilter.h"

#include "equipment/engineslot.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "worldobject/worldobjectcomponents.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket():
    Projectile(),
    m_targetHandle(nullptr),
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
        m_targetHandle = targetObject->handle();
        m_aiTask.reset(new DirectSuicideTask(&m_boardComputer, targetObject));
    } else {
        m_targetHandle = Handle<WorldObject>(nullptr);
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

void Rocket::spawnExplosion() {
    VoxelExplosionGenerator generator(this);

    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFF0000FF);
    generator.setEmissiveness(0.4f);
    generator.setCount(150);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.5f);

    generator.spawn();
}

void Rocket::onLifetimeOver() {
    spawnExplosion();
}

