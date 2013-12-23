
#include "worldobject/ship.h"
#include "camera.h"

class Player
{

public:
    Player(Camera *camera);

    void setShip(Ship *ship);
    void move(glm::vec3 direction);
    void rotate(glm::vec3 direction);
    void applyAcceleration();
    void setFollowCam();
    Ship* playerShip();
    void setShipToCam(float deltaSec);
    void boost();


private:
    Camera *m_camera;
    Ship *m_playerShip;
    glm::vec3 m_shipOffset;
<<<<<<< HEAD
    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;
=======
    glm::vec3 acc;
    glm::vec3 accAng;

>>>>>>> ed12d8382ff65e15ac13dcaf05bf057c505d69e4
};
