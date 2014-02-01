#include <glm/glm.hpp>
#include "weapon.h"
#include "rocket.h"
#include "resource/clustercache.h"

class RocketLauncher : public Weapon {
public:
    RocketLauncher();

    virtual AimType aimType() override;
    virtual float bulletSpeed() const override;
    virtual float range() override;

    virtual void shootAtObject(Hardpoint* source, WorldObject* target) override;
    virtual void update(float deltaSec) override;

private:
    Property<float> m_range;
    Property<float> m_cooldownTime;
    Property<float> m_speed;
    Property<float> m_lifetime;
};
