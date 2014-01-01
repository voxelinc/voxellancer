#include "enginedworldobject.h"

#include "engine.h"
#include "voxel/specialvoxels/enginevoxel.h"

EnginedWorldObject::EnginedWorldObject(CollisionFilterClass collisionFilterClass) :
    WorldObject(collisionFilterClass),
    m_engines()
{
}

void EnginedWorldObject::update(float deltasec){
    for (Engine *engine : m_engines){
        engine->update(deltasec);
    }
}

void EnginedWorldObject::addEngineVoxel(EngineVoxel* voxel){
    Engine* engine = new Engine(this, voxel);
    voxel->setEngine(engine);
    m_engines.push_back(engine);
    addVoxel(voxel);
}

void EnginedWorldObject::removeEngine(Engine* engine){
    std::vector<Engine*>::iterator iterator = m_engines.begin();
    while (iterator != m_engines.end()){
        if (*iterator == engine){
            delete *iterator;
            m_engines.erase(iterator);
            break;
        }
        ++iterator;
    }
}