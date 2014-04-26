#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>




class Transform {
public:
    Transform(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    Transform(const Transform& transform, const glm::vec3& positionDelta, const glm::quat& orientationDelta);
    virtual ~Transform();

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

    bool operator==(const Transform &other) const;
    bool operator!=(const Transform &other) const;

    const glm::mat4 matrix() const;

    glm::vec3 applyTo(const glm::vec3 &vertex) const;
    glm::vec3 inverseApplyTo(const glm::vec3 &vertex) const;

    Transform mixed(const Transform& other, float v);


protected:
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_center;
    float m_scale;
};

