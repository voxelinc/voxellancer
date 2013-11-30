#include <glm/glm.hpp>
#include "bullet.h"
#include "resource/clustercache.h"

class Gun{
public:
    Gun(float speed, float range, float cooldown);
    Bullet *shoot(glm::vec3 position, glm::vec3 direction);
    void update(float delta_sec);

private:
    float m_speed;
    float m_range;
    float m_cooldownTime;
    float m_cooldown;
};