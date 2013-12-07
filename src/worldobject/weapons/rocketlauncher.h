#include <glm/glm.hpp>
#include "launcher.h"
#include "rocket.h"
#include "resource/clustercache.h"

class RocketLauncher : public Launcher {
public:
    RocketLauncher();
    virtual AimType aimType();
    virtual void shootAtObject(Hardpoint* source, WorldObject* target);
    virtual void update(float delta_sec);
    virtual float aimRange();

private:
    Property<float> prop_aimRange, prop_cooldownTime, prop_speed, prop_lifetime;
    float m_cooldown;
};