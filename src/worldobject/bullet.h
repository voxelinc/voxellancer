#include "worldobject\worldobject.h"

class Bullet : public WorldObject{

public:
	Bullet(glm::vec3 position, glm::vec3 direction, float speed, float range);
    virtual void updateSpeed(float delta_sec);
    virtual void update(float delta_sec);

private:
	float m_speed;
	float m_range;
	float m_distance;
};