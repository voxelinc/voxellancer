#pragma once

#include <memory>


class AimHelperHudget;
class VoxelCluster;

class AimHelperHudgetVoxels {
public:
    AimHelperHudgetVoxels(AimHelperHudget* aimHelperHudget);
    ~AimHelperHudgetVoxels();

    void draw();


protected:
    AimHelperHudget* m_aimHelperHudget;
    std::unique_ptr<VoxelCluster> m_dot;
    std::unique_ptr<VoxelCluster> m_circle;
};

