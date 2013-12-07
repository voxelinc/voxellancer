#include <glm/glm.hpp>
#include "launcher.h"
#include "bullet.h"
#include "resource/clustercache.h"

class Gun : public Launcher {
public:
    Gun(float speed, float range, float cooldown);
    virtual AimType aimType();
    virtual void shootAtPoint(glm::vec3 position, glm::quat orientation, glm::vec3 target);
    virtual void update(float delta_sec);
    virtual float range();

private:
    float m_speed;
    float m_range;
    float m_cooldownTime;
    float m_cooldown;
};