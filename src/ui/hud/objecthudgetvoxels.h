#pragma once

#include <vector>

class Ray;
class ObjectHudget;
class ObjectHudgetCorner;

class ObjectHudgetVoxels {
public:
    ObjectHudgetVoxels(ObjectHudget* hudget);
    ~ObjectHudgetVoxels();

    ObjectHudget* hudget();

    float openingAngle() const;
    void setOpeningAngle(float openingAngle);

    void draw();

    bool isAt(const Ray& ray) const;


protected:
    ObjectHudget* m_hudget;
    ObjectHudgetCorner* m_lu;
    ObjectHudgetCorner* m_rb;
    ObjectHudgetCorner* m_lb;
    ObjectHudgetCorner* m_ru;
    float m_openingAngle;

    void setupCorners();
};

