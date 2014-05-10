#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>


class Explosion;

class ExplosionBuilder {
public:
    ExplosionBuilder(const std::string& prefix);

    std::shared_ptr<Explosion> build();


protected:
    std::string m_prefix;

    std::shared_ptr<Explosion> buildScatterExplosion();
};

