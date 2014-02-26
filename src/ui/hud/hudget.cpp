#include "hudget.h"

#include "utils/geometryhelper.h"

#include "hud.h"


Hudget::Hudget(HUD* hud):
    m_hud(hud),
    m_direction(0.0f, 0.0f, -1.0f),
    m_directionAngle(0.0f),
    m_relativeDistance(1.0f),
    m_visible(true),
    m_pressed(false),
    m_hovered(false),
    m_clicked(false),
    m_released(false),
    m_entered(false),
    m_left(false)
{
}


HUD* Hudget::hud() {
    return m_hud;
}

bool Hudget::visible() const {
    return m_visible;
}

void Hudget::setVisible(bool visible) {
    m_visible = visible;
}

bool Hudget::pressed() const {
    return m_pressed && m_visible;
}

bool Hudget::hovered() const {
    return m_hovered && m_visible;
}

bool Hudget::clicked() const {
    return m_clicked && m_visible;
}

bool Hudget::released() const {
    return m_released && m_visible;
}

bool Hudget::entered() const {
    return m_entered && m_visible;
}

bool Hudget::left() const {
    return m_left && m_visible;
}

bool Hudget::isAt(const Ray& ray) const {
    return false;
}

void Hudget::pointerAt(const Ray& ray, bool pressed) {
    m_released = m_pressed && !pressed;

    if (isAt(ray)) {
        m_clicked = pressed && !m_clicked;
        m_entered = !m_hovered;
        m_hovered = true;
        m_pressed = pressed;
        m_left = false;
    } else {
        m_left = m_hovered;
        m_clicked = false;
        m_entered = false;
        m_hovered = false;
        m_pressed = false;
    }
}

void Hudget::setRelativeDistance(float relativeDistance) {
    m_relativeDistance = relativeDistance;
}

void Hudget::pointToWorldPoint(const glm::vec3& worldPoint) {
    m_direction = glm::normalize(glm::inverse(m_hud->orientation()) * (worldPoint - m_hud->position()));
}

void Hudget::pointToLocalPoint(const glm::vec3& localPoint) {
    m_direction = glm::normalize(localPoint);
}

glm::vec3 Hudget::localDirection() const {
    return m_direction;
}

glm::vec3 Hudget::worldDirection() const {
    return m_hud->orientation() * m_direction;
}

float Hudget::directionAngle() const {
    return m_directionAngle;
}

void Hudget::setDirectionAngle(float directionAngle) {
    m_directionAngle = directionAngle;
}

glm::vec3 Hudget::worldPosition() const {
    return worldPosition(m_direction * m_relativeDistance);
}

glm::vec3 Hudget::worldPosition(const glm::vec3& localVector) const {
    return m_hud->position() + m_hud->orientation() * (localVector * m_hud->sphere().radius());
}

glm::quat Hudget::worldOrientation() const {
    return worldOrientation(m_direction * m_relativeDistance);
}

glm::quat Hudget::worldOrientation(const glm::vec3& localVector) const {
    return m_hud->orientation() * GeometryHelper::quatFromViewDirection(localVector * m_hud->sphere().radius()) * glm::quat(glm::vec3(0.0f, 0.0f, m_directionAngle));
}

void Hudget::onClick(int button) {
}

