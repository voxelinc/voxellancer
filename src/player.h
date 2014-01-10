#include "worldobject/ship.h"
#include "camera/camera.h"

class Player
{

public:
    Player();

    void setShip(Ship *ship);

    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);

    void applyAcceleration();

    Ship* playerShip();



private:
    Ship *m_playerShip;
    glm::vec3 m_shipOffset;
    glm::vec3 acc;
    glm::vec3 accAng;
};

