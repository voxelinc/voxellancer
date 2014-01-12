#pragma once

#include <list>

#include <glm/gtx/quaternion.hpp>

#include "cameraeye.h"


class HUD;
class CameraDolly;
class CrossHair;

class CameraHead {
public:
    CameraHead(CameraDolly* cameraDolly);

    CameraDolly* cameraDolly();

    HUD* hud();
    void setHUD(HUD* hud);

    const glm::quat& relativeOrientation() const;

    const std::list<CameraEye*>& eyes() const;

    glm::vec3 position() const;
    glm::quat orientation() const;

    void setupMonoView();
    void setupStereoView();

    void update(float deltaSec);
    void draw();


protected:
    CameraDolly* m_cameraDolly;
    HUD* m_hud;

    glm::quat m_relativeOrientation;

    std::list<CameraEye*> m_eyes;

    int m_viewportWidth;
    int m_viewportHeight;


    void clearEyes();
    void setViewport();
};
