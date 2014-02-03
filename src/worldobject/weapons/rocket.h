#include <memory>

#include "worldobject/ship.h"

#include "worldobject/handle/handle.h"

class Sound;

class Rocket : public Ship {

public:
    Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* creator, WorldObject* target);
    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;

private:
    void spawnExplosion();

    float m_lifetime;
    float m_travelSpeed;
    WorldObject* m_creator;

    std::shared_ptr<Sound> m_sound;
    Handle<WorldObject> m_target;
};
