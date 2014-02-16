#pragma once

#include <string>


class Bullet;
class Rocket;
class Ship;
class VoxelCluster;
class WorldObject;
class WorldObjectComponents;

/*
    Sets up WorldObject by the settinsg provided by properties
*/
class WorldObjectBuilder {
public:
    WorldObjectBuilder(const std::string& name);

    WorldObject* build();

    Bullet* buildBullet();
    Rocket* buildRocket();
    Ship* buildShip();
    WorldObject* buildWorldObject();


protected:
    std::string m_name;

    template<typename WorldObjectType>
    WorldObjectType* newWorldObject();

    void setupVoxelCluster(WorldObject* worldObject);
    void setupComponents(WorldObjectComponents& components);
    void setupHardpoints(WorldObjectComponents& components);
    void setupEngineSlots(WorldObjectComponents& components);
};

#include "worldobjectbuilder.inl"
