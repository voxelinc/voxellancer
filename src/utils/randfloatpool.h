#pragma once

#include <memory>
#include <vector>

/*
    A pool that can be used just as RandFloat except that it is
    faster and values will repeat over time
*/
class RandFloatPool {
public:
    static float rand(float from, float to);
    static float randomize(float value, float randomization);


	static void initialize();

protected:
	static std::vector<float> s_pool;
	static int s_iter;

};

