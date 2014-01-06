
#include "worldobject/ship.h"
#include "camera.h"

class Player
{

public:
    Player(Camera *camera);

    void setShip(Ship *ship);
    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);
    void applyUpdate();
    void setFollowCam();
    Ship* playerShip();
    void setShipToCam(float delta_sec);
    void boost();


private:
    Camera *m_camera;
    Ship *m_playerShip;
    glm::vec3 m_shipOffset;
    glm::vec3 acceleration;
    glm::vec3 accelerationAngular;

};