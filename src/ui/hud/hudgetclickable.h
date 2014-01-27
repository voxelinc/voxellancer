#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

/*
    Baseclass for everything on the HUD that can interact
    with the crosshair/mouse.
*/
class HudgetClickable {
public:
    HudgetClickable();

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
    virtual bool isAt(const glm::quat& quat) const = 0;

    /*
        To be called every frame, clicked shall be true when the
        pointer was clicked in that exact frame
    */
    virtual void pointerAt(const glm::quat& quat, bool pressed);

    virtual void update(float deltaSec);


protected:
    bool m_pressed;
    bool m_hovered;
    bool m_clicked;
    bool m_released;
    bool m_entered;
    bool m_left;
};

