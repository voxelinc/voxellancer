#pragma once

#include <memory>
#include <vector>

#include "factions/factionrelation.h"

class Ray;
class ObjectHudget;
class ObjectHudgetCornerVoxels;


class ObjectHudgetVoxels {
public:
    ObjectHudgetVoxels(ObjectHudget* hudget);
    ~ObjectHudgetVoxels();

    ObjectHudget* hudget();

    void setTargetHightlight(bool targetHightlight);
    void setRelationType(FactionRelationType relationType);

    float openingAngle() const;
    void setOpeningAngle(float openingAngle);

    void update(float deltaSec);
    void draw();

    bool isAt(const Ray& ray) const;


protected:
    ObjectHudget* m_hudget;

    std::unique_ptr<ObjectHudgetCornerVoxels> m_lu;
    std::unique_ptr<ObjectHudgetCornerVoxels> m_lb;
    std::unique_ptr<ObjectHudgetCornerVoxels> m_ru;
    std::unique_ptr<ObjectHudgetCornerVoxels> m_rb;

    float m_openingAngle;
    bool m_targetHightlight;
    FactionRelationType m_relationType;
};

