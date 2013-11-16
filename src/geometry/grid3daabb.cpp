#include "grid3daabb.h"


Grid3dAABB::Grid3dAABB() {

}

Grid3dAABB::Grid3dAABB(const IAABB &iaabb):
    IAABB(iaabb.llf(), iaabb.rub())
{

}

Grid3dAABB::Grid3dAABB(const glm::ivec3 &llf, const glm::ivec3 &rub):
    IAABB(llf, rub)
{

}

int Grid3dAABB::extent(Axis axis) const {
    return m_rub[(int)axis] - m_llf[(int)axis] + 1;
}

std::list<Grid3dAABB> Grid3dAABB::split(Axis axis) const {
    std::list<Grid3dAABB> result;
    Grid3dAABB a, b;

    split(a, b, axis);
    result.push_back(a);
    result.push_back(b);

    return result;
}

void Grid3dAABB::split(Grid3dAABB &a, Grid3dAABB &b, Axis axis) const {
    IAABB::split(a, b, axis);
}

std::list<Grid3dAABB> Grid3dAABB::recursiveSplit(int recursions, Axis axis) const {
    assert(recursions >= 0);

    if(recursions == 0) {
        return split(axis);
    }

    std::list<Grid3dAABB> result, subResult;
    Axis nextAxis;

    subResult = split(axis);

    nextAxis = (Axis)(((int)axis + 1) % 3);

    result.splice(result.end(), subResult.front().recursiveSplit(recursions-1, nextAxis));
    result.splice(result.end(), subResult.back().recursiveSplit(recursions-1, nextAxis));

    return result;
}

bool Grid3dAABB::operator==(const Grid3dAABB &other) const {
    return m_llf == other.llf() && m_rub == other.rub();
}
