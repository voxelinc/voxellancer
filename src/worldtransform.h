#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

/* General Object in our 3D world with position and orientation
*/
class WorldTransform {

public:
    WorldTransform(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    WorldTransform(const WorldTransform& worldTransform, const glm::vec3& positionDelta, const glm::quat& orientationDelta);
	virtual ~WorldTransform();

	const glm::vec3 &position() const;
	void setPosition(const glm::vec3 &pos);

	const glm::quat& orientation() const;
	void setOrientation(const glm::quat& quat);

    const glm::vec3& center() const;
    void setCenter(const glm::vec3& center);
    void setCenterAndAdjustPosition(const glm::vec3& newCenter);

    float scale() const;
    void setScale(float scale);

	void move(const glm::vec3& dist);
    void moveWorld(const glm::vec3& dist);

    void rotate(const glm::quat &qrot);
    void rotateWorld(const glm::quat &qrot);

    bool operator==(const WorldTransform &other);
    bool operator!=(const WorldTransform &other);

	const glm::mat4 matrix() const;
    glm::vec3 applyTo(const glm::vec3 &vertex) const;



protected:
	glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_center;
    float m_scale;

};

