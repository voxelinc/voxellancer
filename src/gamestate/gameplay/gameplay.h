#pragma once

#include "gamestate/gamestate.h"

#include "scenarios/gamescenario.h"

#include "sound/soundmanager.h"

#include "player.h"

#include "gameplayscene.h"




class Game;
class GamePlayMain;
class GamePlayPaused;

class GamePlay: public GameState {
public:
    GamePlay(Game* game);

    Game* game();

    virtual const Scene& scene() const override;
    virtual const CameraHead& cameraHead() const override;

    Player& player();
    SoundManager& soundManager();

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    Game* m_game;

    GamePlayMain* m_mainState;
    GamePlayPaused* m_pausedState;

    GamePlayScene m_scene;
    Player m_player;
    GameScenario m_scenario;
    std::shared_ptr<SoundManager> m_soundManager;
};

