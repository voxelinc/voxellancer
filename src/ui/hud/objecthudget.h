#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"


class ObjectHudgetVoxels;
class HUDObjectDelegate;
class ArrowHudgetVoxels;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud);
    virtual ~ObjectHudget();

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    virtual void onClick(ClickType clickType) override;

    float openingAngle() const;

    HUDObjectDelegate* objectDelegate();
    void setObjectDelegate(HUDObjectDelegate* objectDelegate);


protected:
    HUDObjectDelegate* m_objectDelegate;
    std::unique_ptr<ObjectHudgetVoxels> m_objectVoxels;
    std::unique_ptr<ArrowHudgetVoxels> m_arrowVoxels;

    bool m_targeted;
    void updateTargeted();

    bool m_insideFov;
    float m_fovy, m_fovx;

    bool isInsideFov();
    glm::vec3 closestPointInsideFov();

    void calculateOpeningAngle();

    void updateFov();
};

