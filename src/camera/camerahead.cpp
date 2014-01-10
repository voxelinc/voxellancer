#include "camerahead.h"

#include <GLFW/glfw3.h>

#include "cameradolly.h"


CameraHead::CameraHead(CameraDolly* cameraDolly):
    m_cameraDolly(cameraDolly)
{
    setupMonoView();
}

CameraDolly* CameraHead::cameraDolly() {
    return m_cameraDolly;
}

const glm::quat& CameraHead::relativeOrientation() const {
    return m_relativeOrientation;
}

glm::vec3 CameraHead::position() const {
    return m_cameraDolly->position();
}

glm::quat CameraHead::orientation() const {
    return m_cameraDolly->orientation() + m_relativeOrientation;
}

void CameraHead::setupMonoView() {
    clearEyes();
    setViewport();

    m_eyes.push_back(new CameraEye(this, m_viewportWidth, m_viewportHeight, glm::vec3(0.0f, 0.0f, 0.0f)));
}

void CameraHead::setupStereoView() {
    clearEyes();
    setViewport();

    m_eyes.push_back(new CameraEye(this, m_viewportWidth/2, m_viewportHeight, glm::vec3( 1.0f, 0.0f, 0.0f)));
    m_eyes.push_back(new CameraEye(this, m_viewportWidth/2, m_viewportHeight, glm::vec3(-1.0f, 0.0f, 0.0f)));
}

void CameraHead::update(float deltaSec) {
    for(CameraEye* eye : m_eyes) {
        eye->update(deltaSec);
    }
}

void CameraHead::draw() {
    for(CameraEye* eye : m_eyes) {
        eye->draw();
    }
}

void CameraHead::clearEyes() {
    for(CameraEye* eye : m_eyes) {
        delete eye;
    }
    m_eyes.clear();
}

void CameraHead::setViewport() {
    glfwGetWindowSize(glfwGetCurrentContext(), &m_viewportWidth, &m_viewportHeight);
}

