#include <glm/glm.hpp>
#include "launcher.h"
#include "bullet.h"
#include "resource/clustercache.h"

class Gun : public Launcher {
public:
    Gun();
    virtual AimType aimType();
    virtual void shootAtPoint(Hardpoint* source, glm::vec3 target);
    virtual void update(float delta_sec);
    virtual float aimRange();

private:
    Property<float> prop_aimRange, prop_cooldownTime, prop_speed;

    float m_cooldown;
};