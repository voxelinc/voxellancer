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
    ~CameraHead();

    CameraDolly* cameraDolly();

    HUD* hud();
    void setHUD(HUD* hud);

    const glm::quat& relativeOrientation() const;

    const std::list<CameraEye*>& eyes() const;

    float fovy() const;
    float nearZ() const;
    float farZ() const;
    float aspectRatio() const;

    glm::vec3 position() const;
    glm::quat orientation() const;

    void setupMonoView();
    void setupStereoView();

    void update(float deltaSec);
    void draw();


protected:
    CameraDolly* m_cameraDolly;
    HUD* m_hud;

    HMD* m_oculus;
    HMDManager m_oculusManager;

    MonoBlitProgram m_monoBlitProgram;
    StereoBlitProgram m_stereoBlitProgram;

    ScreenBlitter m_screenBlitter;

    glm::quat m_relativeOrientation;

    std::list<CameraEye*> m_eyes;

    Viewport m_viewport;

    void clearEyes();
    void setViewport();

    bool viewportDirty();
    void viewportChanged();
};

