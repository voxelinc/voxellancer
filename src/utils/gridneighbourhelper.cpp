#include "gridneighbourhelper.h"


namespace {
    const std::vector<glm::ivec3> directNeighbours {
        glm::ivec3(-1, 0, 0),
        glm::ivec3(1, 0, 0),
        glm::ivec3(0, -1, 0),
        glm::ivec3(0, 1, 0),
        glm::ivec3(0, 0, -1),
        glm::ivec3(0, 0, 1)
    };

    const std::vector<glm::ivec3> diagonalNeighbours {
        glm::ivec3(-1, -1, -1),
        glm::ivec3(0, -1, -1),
        glm::ivec3(1, -1, -1),
        glm::ivec3(-1, 0, -1),
        glm::ivec3(1, 0, -1),
        glm::ivec3(-1, 1, -1),
        glm::ivec3(0, 1, -1),
        glm::ivec3(1, 1, -1),
        glm::ivec3(-1, -1, 0),
        glm::ivec3(1, -1, 0),
        glm::ivec3(-1, 1, 0),
        glm::ivec3(1, 1, 0),
        glm::ivec3(-1, -1, 1),
        glm::ivec3(0, -1, 1),
        glm::ivec3(1, -1, 1),
        glm::ivec3(-1, 0, 1),
        glm::ivec3(1, 0, 1),
        glm::ivec3(-1, 1, 1),
        glm::ivec3(0, 1, 1),
        glm::ivec3(1, 1, 1)
    };
}




GridNeighbourHelper::GridNeighbourHelper(const glm::ivec3& cell, bool includeDiagonals) {
    m_neighbours.reserve(includeDiagonals ? 26 : 6);

    for (const glm::ivec3& neighbour : directNeighbours) {
        m_neighbours.push_back(neighbour + cell);
    }

    if (includeDiagonals) {
        for (const glm::ivec3& neighbour : diagonalNeighbours) {
            m_neighbours.push_back(neighbour + cell);
        }
    }
}

const std::vector<glm::ivec3>& GridNeighbourHelper::neighbours() const {
    return m_neighbours;
}

