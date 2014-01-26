#pragma once

class AimHelperHudget;

class AimHelperHudgetVoxels {
public:
    AimHelperHudgetVoxels(AimHelperHudget* aimHelperHudget);

    void draw();

protected:
    AimHelperHudget* m_aimHelperHudget;
};

