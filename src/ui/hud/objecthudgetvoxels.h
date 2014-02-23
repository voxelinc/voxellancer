#pragma once

#include <memory>
#include <vector>


class ObjectHudget;
class ObjectHudgetCornerVoxels;


class ObjectHudgetVoxels {
public:
    ObjectHudgetVoxels(ObjectHudget* hudget);
    ~ObjectHudgetVoxels();

    ObjectHudget* hudget();

    void setTargetHightlight(bool targetHightlight);

    float openingAngle() const;
    void setOpeningAngle(float openingAngle);

    void draw();


protected:
    ObjectHudget* m_hudget;

    std::unique_ptr<ObjectHudgetCornerVoxels> m_lu[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_lb[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_ru[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_rb[2];

    float m_openingAngle;
    bool m_targetHightlight;

    void setupCorners();
};

