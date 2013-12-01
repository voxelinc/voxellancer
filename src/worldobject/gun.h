#include <glm/glm.hpp>
#include "bullet.h"
#include "resource/clustercache.h"

class Gun{
public:
    Gun(float speed, float range, float cooldown);
    Bullet* shootAt(glm::vec3 position, glm::quat orientation, glm::vec3 direction);
    void update(float delta_sec);
    float range();

private:
    float m_speed;
    float m_range;
    float m_cooldownTime;
    float m_cooldown;
};