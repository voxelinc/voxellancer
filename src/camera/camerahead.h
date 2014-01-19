#pragma once

#include <list>

#include <glow/Program.h>

#include <glm/gtx/quaternion.hpp>

#include "etc/oculus/oculusmanager.h"

#include "utils/screenblitter.h"

#include "geometry/viewport.h"
#include "programs/monoblitprogram.h"
#include "programs/stereoblitprogram.h"

#include "cameraeye.h"


class HUD;
class CameraDolly;
class CrossHair;

class CameraHead {
public:
    CameraHead(CameraDolly* cameraDolly);

    CameraDolly* cameraDolly();

    const glm::quat& relativeOrientation() const;
    void setRelativeOrientation(const glm::quat& relativeOrientation);

    float fovy() const;
    float nearZ() const;
    float farZ() const;
    float aspectRatio() const;

    glm::vec3 position() const;
    glm::quat orientation() const;
g

protected:
    CameraDolly* m_cameraDolly;

    glm::quat m_relativeOrientation;
};

