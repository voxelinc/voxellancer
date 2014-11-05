#include "voxelcollisionaccumulator.h"

#include <map>
#include <cassert>

#include "worldobject/worldobject.h"


struct WorldObjectPair {
    WorldObjectPair(WorldObject *a, WorldObject *b) {
        if(a < b) {
            this->a = a;
            this->b = b;
        }
        else {
            this->a = b;
            this->b = a;
        }
    }

    bool operator<(const WorldObjectPair& other) const {
        return a < other.a ? true : other.a < a ? false : b < other.b;
    }

    WorldObject *a;
    WorldObject *b;
};


void VoxelCollisionAccumulator::parse(std::list<VoxelCollision>& voxelCollisions) {
    std::map<WorldObjectPair, WorldObjectCollision*> worldObjectCollisionMap;
    std::set<WorldObject*> worldObjectSet;

    m_worldObjectCollisions.clear();
    m_worldObjects.clear();

    for(VoxelCollision& voxelCollision : voxelCollisions) {
        WorldObjectCollision* worldObjectCollision;
        WorldObjectPair worldObjectPair(voxelCollision.a().worldObject(), voxelCollision.b().worldObject());
        std::map<WorldObjectPair, WorldObjectCollision*>::iterator i = worldObjectCollisionMap.find(worldObjectPair);

        if(i == worldObjectCollisionMap.end()) {
            worldObjectCollision = new WorldObjectCollision(worldObjectPair.a, worldObjectPair.b);
            worldObjectCollisionMap[worldObjectPair] = worldObjectCollision;
        }
        else {
            worldObjectCollision = i->second;
        }

        worldObjectCollision->addVoxelCollision(voxelCollision);

        worldObjectSet.insert(voxelCollision.a().worldObject());
        worldObjectSet.insert(voxelCollision.b().worldObject());
    }

    for(std::pair<const WorldObjectPair, WorldObjectCollision*>& p : worldObjectCollisionMap) {
        assert(p.second != nullptr);
        m_worldObjectCollisions.push_back(*p.second);
        delete p.second;
    }

    m_worldObjects.assign(worldObjectSet.begin(), worldObjectSet.end());
}

void VoxelCollisionAccumulator::applyOnCollsionHooks(){
    for (WorldObjectCollision collision : m_worldObjectCollisions) {
        collision.worldObjectA()->onCollisionWith(collision.worldObjectB());
        collision.worldObjectB()->onCollisionWith(collision.worldObjectA());
    }
    for (WorldObject* object : m_worldObjects){
        object->onCollision();
    }
}

std::list<WorldObjectCollision>& VoxelCollisionAccumulator::worldObjectCollisions() {
    return m_worldObjectCollisions;
}
std::list<WorldObject*>& VoxelCollisionAccumulator::worldObjects() {
    return m_worldObjects;
}
