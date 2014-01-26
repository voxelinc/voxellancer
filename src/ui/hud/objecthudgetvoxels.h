#pragma once

#include <vector>

#include "voxel/voxelcluster.h"


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


protected:
    ObjectHudget* m_hudget;
    ObjectHudgetCorner* m_lu;
    ObjectHudgetCorner* m_lb;
    ObjectHudgetCorner* m_ru;
    ObjectHudgetCorner* m_rb;
    float m_openingAngle;

    void setupCorners();
};

