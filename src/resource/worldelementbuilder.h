#pragma once

#include <string>


class Bullet;
class InstancedBullet;
class Rocket;
class Ship;
class VoxelCluster;
class WorldObject;
class WorldObjectBullet;
class WorldObjectComponents;

/**
 *  Sets up WorldObject by the settings provided by properties
 */
class WorldElementBuilder {
public:
    WorldElementBuilder(const std::string& name);

    WorldObject* buildWorldObject();

    Bullet* buildBullet();
    InstancedBullet* buildInstancedBullet();
    WorldObjectBullet* buildWorldObjectBullet();
    Rocket* buildRocket();
    Ship* buildShip();
    WorldObject* buildOther();



protected:
    std::string m_name;

    template<typename T>
    T* makeWorldObject();

    void setupVoxelCluster(WorldObject* worldObject);
    void setupComponents(WorldObjectComponents& components);
    void setupHardpoints(WorldObjectComponents& components);
    void setupEngineSlots(WorldObjectComponents& components);
    void setupShieldSlots(WorldObjectComponents& components);


    /**
     * Little hack method that ensures all hardpoints and engine-points are equipped
     * with something
     */
    void equipSomehow(WorldObject* worldObject);
};

