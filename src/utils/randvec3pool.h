#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>


/*
	A pool that can be used like RandVec3 except that the retrieval
	will be much faster and	the values will repeat again in the same order over time.
*/
class RandVec3Pool {
public:
	static std::shared_ptr<RandVec3Pool> instance();

	glm::vec3 randUnitVec();


protected:
	std::vector<glm::vec3> m_pool;
	int m_iter;

	static std::weak_ptr<RandVec3Pool> s_instance;


	RandVec3Pool();
};

