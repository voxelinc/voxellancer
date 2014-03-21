#pragma once

#include <memory>
#include <vector>


class RandFloatPool {
public:
    static std::shared_ptr<RandFloatPool> instance();

    float rand(float from, float to);
    float randomize(float value, float randomization);


protected:
	std::vector<float> m_pool;
	int m_iter;

	static std::weak_ptr<RandFloatPool> s_instance;


	RandFloatPool();
};
