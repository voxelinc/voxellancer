#pragma once

#include <list>

#include <glm/gtx/quaternion.hpp>


class HUD;
class CameraDolly;
class CrossHair;

class CameraHead {
public:
    CameraHead(CameraDolly* cameraDolly);

    CameraDolly* cameraDolly();

    const glm::quat& relativeOrientation() const;
    void setRelativeOrientation(const glm::quat& relativeOrientation);

    glm::vec3 position() const;
    glm::quat orientation() const;


protected:
    CameraDolly* m_cameraDolly;

    glm::quat m_relativeOrientation;
};

