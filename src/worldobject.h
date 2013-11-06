#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/* General Object in our 3D world with position and orientation
*/
class WorldObject {

public:
	WorldObject();
	virtual ~WorldObject();

    void move(glm::vec3 dist);

    void rotateX(float rot);
    void rotateY(float rot);
    void rotateZ(float rot);

    const glm::mat4 matrix();
    const glm::quat orientation();

private:
    glm::vec3 m_position;
    glm::quat m_orientation;

};