#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

/* General Object in our 3D world with position and orientation
*/
class WorldTransform {

public:
	WorldTransform();
	virtual ~WorldTransform();

	void clear();

	void move(glm::vec3 dist);
	void moveTo(glm::vec3 pos);

	void rotateX(float rot);
	void rotateY(float rot);
	void rotateZ(float rot);
	void rotateTo(glm::quat quat);

	void add(const WorldTransform &other);

	const glm::vec3 &position() const;

	const glm::mat4 matrix() const;
	const glm::quat orientation() const;

protected:
	glm::vec3 m_position;
    glm::quat m_orientation;
};

