#pragma once

#include <vector>


class ObjectHudget;

namespace {
    class ObjectHudgetCorner;
}

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

    ObjectHudgetCorner* m_lu[2];
    ObjectHudgetCorner* m_lb[2];
    ObjectHudgetCorner* m_ru[2];
    ObjectHudgetCorner* m_rb[2];

    float m_openingAngle;
    bool m_targetHightlight;

    void setupCorners();
};

