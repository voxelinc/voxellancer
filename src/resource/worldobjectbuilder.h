#pragma once

#include <string>


class Ship;
class WorldObject;

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
};

