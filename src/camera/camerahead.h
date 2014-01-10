#pragma once

#include <list>

#include <glm/gtx/quaternion.hpp>

#include "cameraeye.h"


class CameraDolly;

class CameraHead {
public:
    CameraHead(CameraDolly* cameraDolly);

    CameraDolly* cameraDolly();

    const glm::vec3& relativeOrientation() const;

    glm::vec3 position() const;
    glm::vec3 orientation() const;

    void setupMonoView();
    void setupStereoView();

    void update(float deltaSec);
    void draw();


protected:
    CameraDolly* m_cameraDolly;

    glm::vec3 m_relativeOrientation;

    std::list<CameraEye*> m_eyes;

    int m_viewportWidth;
    int m_viewportHeight;


    void clearEyes();
    void setViewport();
};
