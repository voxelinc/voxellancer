#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

/* General Object in our 3D world with position and orientation
*/
class WorldTransform {

public:
	WorldTransform();
	WorldTransform(const glm::vec3 &position);
	WorldTransform(const glm::quat &orientation);
	virtual ~WorldTransform();

	void clear();

	const glm::vec3 &position() const;
	void setPosition(glm::vec3 pos);

	const glm::quat orientation() const;
	void setOrientation(glm::quat quat);


	void move(glm::vec3 dist);

	void rotateX(float rot);
	void rotateY(float rot);
	void rotateZ(float rot);

	void transform(const WorldTransform &other);

	const glm::mat4 matrix() const;

	void applyTo(glm::vec3 &vertex) const;


protected:
	glm::vec3 m_position;
    glm::quat m_orientation;
};

