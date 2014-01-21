#include <glm/glm.hpp>
#include "weapon.h"
#include "rocket.h"
#include "resource/clustercache.h"

class RocketLauncher : public Weapon {
public:
    RocketLauncher();

    virtual AimType aimType() override;
    virtual void shootAtObject(Hardpoint* source, WorldObject* target) override;
    virtual void update(float deltaSec) override;
    virtual float bulletRange() override;

private:
    Property<float> m_bulletRange;
    Property<float> m_cooldownTime;
    Property<float> m_speed;
    Property<float> m_lifetime;
};
