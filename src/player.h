
#include "worldobject/ship.h"
#include "camera.h"

class Player
{

public:
    Player(Camera *camera);

    void setShip(Ship *ship);
    void accelerateShip(glm::vec3 direction);
    void accelerateAngularShip(glm::vec3 direction);
    void setFollowCam();
    Ship* playerShip();
    void setShipToCam();


private:
    Camera *m_camera;
    Ship *m_playerShip;
    glm::vec3 m_shipOffset;

};