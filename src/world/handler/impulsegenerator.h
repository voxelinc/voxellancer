#pragma once

#include <list>

#include "collision/worldobjectcollision.h"

#include "physics/impulse.h"


class ImpulseGenerator {
public:
    void parse(std::list<WorldObjectCollision>& worldObjectCollisions);

    std::list<Impulse>& worldObjectImpulses();


protected:
    std::list<Impulse> m_worldObjectImpulses;

    void generateImpulse(VoxelCollisionParticipant &from, VoxelCollisionParticipant &to);
};

