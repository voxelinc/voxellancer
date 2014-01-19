#include "camerahead.h"

#include <GLFW/glfw3.h>

#include "etc/oculus/oculusinfo.h"

#include "geometry/viewport.h"

#include "ui/hud.h"

#include "utils/screenblitter.h"
#include "utils/metrics.h"

#include "cameradolly.h"


CameraHead::CameraHead(CameraDolly* cameraDolly):
    m_cameraDolly(cameraDolly),
    m_hud(nullptr),
    m_oculus(nullptr),
    m_viewport(0, 0, 0, 0)
{
    setupStereoView();
}

CameraHead::~CameraHead() {
    delete m_oculus;
}

CameraDolly* CameraHead::cameraDolly() {
    return m_cameraDolly;
}

HUD* CameraHead::hud() {
    return m_hud;
}

void CameraHead::setHUD(HUD* hud) {
    m_hud = hud;
}

const glm::quat& CameraHead::relativeOrientation() const {
    return m_relativeOrientation;
}

const std::list<CameraEye*>& CameraHead::eyes() const {
    return m_eyes;
}

float CameraHead::fovy() const {
    return m_eyes.front()->camera().fovy();
}

float CameraHead::nearZ() const {
    return m_eyes.front()->camera().zNear();
}

float CameraHead::farZ() const {
    return m_eyes.front()->camera().zFar();
}

float CameraHead::aspectRatio() const {
    return m_eyes.front()->camera().aspectRatio();
}

glm::vec3 CameraHead::position() const {
    return m_cameraDolly->position();
}

glm::quat CameraHead::orientation() const {
    return m_cameraDolly->orientation() * m_relativeOrientation;
}

void CameraHead::setupMonoView() {
    clearEyes();
    setViewport();

    m_eyes.push_back(new CameraEye(this, Viewport(0, 0, m_viewport.width(), m_viewport.height()), glm::vec3(0.0f, 0.0f, 0.0f)));

    m_screenBlitter.setProgram(&m_monoBlitProgram);
}

void CameraHead::setupStereoView() {
    clearEyes();
    setViewport();

    if(m_oculus == nullptr) {
        m_oculus = m_oculusManager.oculus();
    }

    assert(m_oculus);
    StereoRenderInfo oculusInfo = m_oculus->info();

    glm::vec3 interpupillaryOffset(Metrics::instance()->toGameUnits(oculusInfo.interpupillaryDistance()), 0.0f, 0.0f);

    CameraEye* leftEye = new CameraEye(this, Viewport(0, 0, m_viewport.width()/2,  m_viewport.height()), -interpupillaryOffset, oculusInfo.distortionScale());
    CameraEye* rightEye = new CameraEye(this, Viewport(m_viewport.width()/2, 0, m_viewport.width()/2,  m_viewport.height()), interpupillaryOffset, oculusInfo.distortionScale());

    float halfScreenDistance = oculusInfo.vScreenSize() / 2.0f;

    leftEye->camera().setFovy(oculusInfo.fovy());
    rightEye->camera().setFovy(oculusInfo.fovy());

    float viewCenter = oculusInfo.hScreenSize() * 0.25f;
    float eyeProjectionShift = viewCenter - oculusInfo.lensSeparationDistance() * 0.5f;
    float projectionCenterOffset = 4.0f * eyeProjectionShift / oculusInfo.hScreenSize();

    leftEye->camera().setProjectionOffset(glm::vec3(projectionCenterOffset, 0.0f, 0.0f));
    rightEye->camera().setProjectionOffset(-glm::vec3(projectionCenterOffset, 0.0f, 0.0f));

    m_eyes.push_back(leftEye);
    m_eyes.push_back(rightEye);

    m_stereoBlitProgram.setDistortionKs(oculusInfo.distortionKs());
    m_stereoBlitProgram.setDistortionScale(oculusInfo.distortionScale());
    m_stereoBlitProgram.setLensCenter(oculusInfo.lensCenter());

    m_screenBlitter.setProgram(&m_stereoBlitProgram);
}

void CameraHead::update(float deltaSec) {
    if(m_oculus == nullptr && m_eyes.size() == 2) {
        m_oculus = m_oculusManager.oculus();
    }

    if(m_oculus != nullptr) {
        m_relativeOrientation = m_oculus->orientation();
    }

    if(viewportDirty()) {
        viewportChanged();
    }

    for (CameraEye* eye : m_eyes) {
        eye->update(deltaSec);
    }
}

void CameraHead::draw() {
    for (CameraEye* eye : m_eyes) {
        eye->draw();
    }

    glViewport(0, 0, m_viewport.width(), m_viewport.height());
    for (CameraEye* eye : m_eyes) {
        m_screenBlitter.blit(eye->fbo(), eye->viewport());
    }
}

void CameraHead::clearEyes() {
    for(CameraEye* eye : m_eyes) {
        delete eye;
    }
    m_eyes.clear();
}

void CameraHead::setViewport() {
    int width;
    int height;

    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    m_viewport = Viewport(0, 0, width, height);
}

bool CameraHead::viewportDirty() {
    int width;
    int height;

    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    return width != m_viewport.width() || height != m_viewport.height();
}

void CameraHead::viewportChanged() {
    if (m_eyes.size() == 1) {
        setupMonoView();
    } else if(m_eyes.size() == 2) {
        setupStereoView();
    } else {
        assert(0);
    }
}

