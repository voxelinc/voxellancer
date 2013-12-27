#include "worldobject/worldobject.h"
#include "resource/clustercache.h"

class Rocket : public WorldObject {

public:
    Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* target);
    virtual void update(float deltaSec);

    virtual void onCollision() override;
    virtual void onSpawnFail() override;

private:
	float m_lifetime;
    float m_travelSpeed;
    WorldObject* m_target;
};
