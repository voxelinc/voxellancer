#pragma once

#include <memory>


class SoundManager;
class Player;
class InputHandler;
class Viewer;
class GameScene;
class Scenario;
class HMDManager;

class Game {
public:
    Game();
    ~Game();

    InputHandler& inputHandler();
    Player& player();
    Viewer& viewer();
    HMDManager& hmdManager();

    void update(float deltaSec);
    void draw();

    void setOutputBuffer(int i);


private:
    std::unique_ptr<Viewer> m_viewer;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<GameScene> m_gameScene;
    std::unique_ptr<GameScenario> m_scenario;
    std::unique_ptr<Scenario> m_scenario;
    std::unique_ptr<HMDManager> m_hmdManager;
};

