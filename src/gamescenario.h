#pragma once


class Game;
class Ship;

class GameScenario {
public:
    GameScenario();

    void populate(Game* game);
    void update(float deltaSec);


protected:
    Ship *m_normandy;
    Ship *m_aimTester;
};

