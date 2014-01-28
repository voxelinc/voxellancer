#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/ray.h"


class HUD;


/*
    Hudget, named after Widget - is an element on the HUD
*/
class Hudget {
public:
    Hudget(HUD* hud);

    HUD* hud();

    bool visible() const;
    void setVisible(bool visible);

    bool pressed() const;
    bool hovered() const;

    bool clicked() const;
    bool released() const;

    bool entered() const;
    bool left() const;

    /*
        Shall return true when the Clickable is under a
        pointer at quat orientation
    */
    virtual bool isAt(const Ray& ray) const;

    /*
        To be called every frame, clicked shall be true when the
        pointer was clicked in that exact frame
    */
    virtual void pointerAt(const Ray& ray, bool pressed);

    virtual glm::vec3 position() const = 0;
    virtual glm::quat orientation() const = 0;

    virtual void update(float deltaSec) = 0;
    virtual void draw() = 0;


protected:
    HUD* m_hud;

    bool m_visible;

    bool m_pressed;
    bool m_hovered;
    bool m_clicked;
    bool m_released;
    bool m_entered;
    bool m_left;
};

