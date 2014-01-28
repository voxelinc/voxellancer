#include "hudget.h"

#include "hud.h"


Hudget::Hudget(HUD* hud):
    m_hud(hud),
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

bool Hudget::pressed() const {
    return m_pressed;
}

bool Hudget::hovered() const {
    return m_hovered;
}

bool Hudget::clicked() const {
    return m_clicked;
}

bool Hudget::released() const {
    return m_released;
}

bool Hudget::entered() const {
    return m_entered;
}

bool Hudget::left() const {
    return m_left;
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
