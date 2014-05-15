#pragma once

#include <memory>

#include "gamestate/gamestate.h"


class BaseScenario;
class Game;
class GamePlayRunning;
class GamePlayPaused;
class GamePlayScene;
class GamePlayInput;
class GamePlayNormalInput;
class GamePlayFreecamInput;
class Player;
class SoundManager;
class Universe;

/**
 * State that is active whenever the the game is actually played and not
 * in some menustate etc.
 */
class GamePlay: public GameState {
public:
    GamePlay(Game* game);

    Game* game();

    GamePlayScene& scene();

    GamePlayRunning& running();
    GamePlayPaused& paused();

    Universe& universe();

    bool freecamActive() const;
    void setFreecamActive(bool active);

    virtual const Scene& scene() const override;
    virtual const CameraHead& cameraHead() const override;

    virtual InputHandler& inputHandler() override;

    SoundManager& soundManager();

    void loadScenario(int i);

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;

    void updateView();


protected:
    Game* m_game;

    std::unique_ptr<Universe> m_universe;

    std::unique_ptr<GamePlayScene> m_scene;
    std::shared_ptr<SoundManager> m_soundManager;

    std::unique_ptr<BaseScenario> m_scenario;

    GamePlayRunning* m_runningState;
    GamePlayPaused* m_pausedState;

    std::unique_ptr<GamePlayNormalInput> m_normalInput;
    std::unique_ptr<GamePlayFreecamInput> m_freecamInput;

    bool m_freecamActive;
};

