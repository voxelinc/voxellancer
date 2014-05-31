#include "boardcomputer.h"

class Player;
class HUD;
class Aimer;
class TargetSelector;
class Ship;

class PlayerBoardComputer : public BoardComputer {
public:
    PlayerBoardComputer(Ship* ship, HUD* hud, TargetSelector* targetSelector);

    void fire(glm::vec3 shootDirection);
    void fireRocket();

    void move(const glm::vec3& vec);
    void rotate(const glm::vec3& euler);

    void setShip(Ship* ship);

    virtual void update(float deltaSec) override;

protected:
    HUD* m_hud;
    Ship* m_ship;
    TargetSelector* m_targetSelector;
    std::unique_ptr<Aimer> m_aimer;
    OrderPriority m_playerOrderPriority;
};

