#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/ray.h"

enum class ClickType;
class HUD;


/**
 * Hudget, named after Widget - is an element on the HUD
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



    virtual void onClick(ClickType clickType);

    /**
     * Shall return true when the Clickable is under a
     * pointer at quat orientation
     */
    virtual bool isAt(const Ray& ray) const;

    /**
     * To be called every frame, clicked shall be true when the
     * pointer was clicked in that exact frame
     */
    virtual void pointerAt(const Ray& ray, bool pressed);

    /**
     * Set the relative distance from the HUD center, where 1.0f
     * is exactly on the HUD-sphere
     */
    void setRelativeDistance(float relativeDistance);

    /**
     * Set the direction the hudget shall point, either to a
     * position in the world or one in the local coordinate system
     */
    void pointToWorldPoint(const glm::vec3& worldPoint);
    void pointToLocalPoint(const glm::vec3& localPoint);

    glm::vec3 localDirection() const;
    glm::vec3 worldDirection() const;

    /**
     * Additionally to the direction, a rotation on the direction-vector
     * can be added to orientate the hudget
     */
    float directionAngle() const;
    void setDirectionAngle(float directionAngle);


    /**
     * Since the Hudgets need to be placed in world-coordinates
     * to make stereo-rendering easier, these functions can be used
     * to retrieve world-coordinates
     */
    glm::vec3 worldPosition() const;
    glm::vec3 worldPosition(const glm::vec3& localVector) const;
    glm::quat worldOrientation() const;
    glm::quat worldOrientation(const glm::vec3& localVector) const;

    virtual void update(float deltaSec) = 0;
    virtual void draw() = 0;


protected:
    HUD* m_hud;

    glm::vec3 m_direction;
    float m_directionAngle;
    float m_relativeDistance;

    bool m_visible;

    bool m_pressed;
    bool m_hovered;
    bool m_clicked;
    bool m_released;
    bool m_entered;
    bool m_left;
};

