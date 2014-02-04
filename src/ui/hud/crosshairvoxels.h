#pragma once

#include <list>

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"


class CrossHair;
class CrossHairElement;

class CrossHairVoxels {
public:
    CrossHairVoxels(CrossHair* crossHair);
    ~CrossHairVoxels();

    void update(float deltaSec);
    void draw();


protected:
    CrossHair* m_crossHair;
    std::list<CrossHairElement*> m_crossHairElements;
};
