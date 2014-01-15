#include "camerahead.h"

#include <GLFW/glfw3.h>

#include "geometry/viewport.h"

#include "ui/hud.h"
#include "utils/screenblitter.h"

#include "cameradolly.h"


CameraHead::CameraHead(CameraDolly* cameraDolly):
    m_cameraDolly(cameraDolly),
    m_hud(nullptr),
    m_viewport(0, 0, 0, 0)
{
    setupStereoView();
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

    m_screenBlitter.setProgram(&m_monoProgram);
}

void CameraHead::setupStereoView() {
    clearEyes();
    setViewport();

    m_eyes.push_back(new CameraEye(this, Viewport(0, 0, m_viewport.width()/2,  m_viewport.height()), glm::vec3(-2.0f, 0.0f, 0.0f)));
    m_eyes.push_back(new CameraEye(this, Viewport(m_viewport.width()/2, 0, m_viewport.width()/2,  m_viewport.height()), glm::vec3(2.0f, 0.0f, 0.0f)));

    m_screenBlitter.setProgram(&m_monoProgram);
}

void CameraHead::update(float deltaSec) {
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

