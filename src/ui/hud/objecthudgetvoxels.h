#pragma once

#include <memory>
#include <vector>

<<<<<<< HEAD
class Ray;
=======
#include "factions/factionrelation.h"


>>>>>>> d04ee8921f9dfbf7b952f1a5cf0cca1cbe75a42b
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

    void draw();

    bool isAt(const Ray& ray) const;


protected:
    ObjectHudget* m_hudget;
    std::unique_ptr<ObjectHudgetCornerVoxels> m_lu[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_lb[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_ru[2];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_rb[2];

    std::unique_ptr<ObjectHudgetCornerVoxels> m_lu[10];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_lb[10];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_ru[10];
    std::unique_ptr<ObjectHudgetCornerVoxels> m_rb[10];

    float m_openingAngle;
    bool m_targetHightlight;
    FactionRelationType m_relationType;

    void setupCorners();
    void addCornerSet(int index, uint32_t color);
};

