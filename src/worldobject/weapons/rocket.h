#include "worldobject/ship.h"
#include "resource/clustercache.h"

#include "worldobject/worldobjecthandle.h"

class Rocket : public Ship {

public:
    Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* target);
    virtual void update(float deltaSec);

    virtual void onCollision() override;
    virtual void onSpawnFail() override;

private:
    void spawnExplosion();

	float m_lifetime;
    float m_travelSpeed;
    std::shared_ptr<WorldObjectHandle> m_target;
};
