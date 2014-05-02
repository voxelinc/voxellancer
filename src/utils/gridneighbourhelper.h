#pragma once

#include <vector>

#include <glm/glm.hpp>


class GridNeighbourHelper {
public:
	GridNeighbourHelper(const glm::ivec3& cell, bool includeDiagonals);

	const std::vector<glm::ivec3>& neighbours() const;


protected:
	std::vector<glm::ivec3> m_neighbours;
};
