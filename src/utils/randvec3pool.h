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
	static glm::vec3 randUnitVec();

    class _Init {
    public:
        _Init();
    };

protected:
	static std::vector<glm::vec3> s_pool;
	static int s_iter;

	static void initialize();
};

