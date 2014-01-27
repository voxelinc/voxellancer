#include "hudgetclickable.h"

HudgetClickable::HudgetClickable():
    m_pressed(false),
    m_hovered(false),
    m_clicked(false),
    m_released(false),
    m_entered(false),
    m_left(false)
{
}

bool HudgetClickable::pressed() const {
    return m_pressed;
}

bool HudgetClickable::hovered() const {
    return m_hovered;
}

bool HudgetClickable::clicked() const {
    return m_clicked;
}

bool HudgetClickable::released() const {
    return m_released;
}

bool HudgetClickable::entered() const {
    return m_entered;
}

bool HudgetClickable::left() const {
    return m_left;
}

void HudgetClickable::pointerAt(const glm::quat& quat, bool pressed) {
    m_released = m_pressed && !pressed;

    if (isAt(quat)) {
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

void HudgetClickable::update(float deltaSec) {

}
