#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Player {

public:
    Player();

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