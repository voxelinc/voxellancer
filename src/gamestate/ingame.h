#pragma once

#include "display/ingamescene.h"

#include "scenarios/gamescenario.h"

#include "sound/soundmanager.h"

#include "ui/inputhandler.h"

#include "player.h"

#include "gamestate.h"




class Game;

class InGame: public GameState {
public:
    InGame(Game* game);

    Game* game();

    InGameScene& scene();
    InputHandler& inputHandler();
    Player& player();

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    Game* m_game;
    InGameScene m_scene;
    InputHandler m_inputHandler;
    Player m_player;
    GameScenario m_scenario;
    std::shared_ptr<SoundManager> m_soundManager;
};

