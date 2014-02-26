#include "gameplay.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/running/gameplayrunning.h"
#include "gamestate/gameplay/paused/gameplaypaused.h"
#include "gameplayscene.h"

#include "utils/statemachine/trigger.h"
#include "utils/statemachine/triggeredtransition.h"

#include "scenarios/basescenario.h"
#include "scenarios/battlescenario.h"
#include "scenarios/gamescenario.h"

#include "sound/soundmanager.h"

#include "world/world.h"

#include "player.h"



GamePlay::GamePlay(Game* game):
    GameState("In Game", game),
    m_game(game),
    m_player(new Player(this)),
    m_runningState(new GamePlayRunning(this)),
    m_pausedState(new GamePlayPaused(this)),
    m_scene(new GamePlayScene(this, *m_player)),
    m_soundManager(new SoundManager()),
    m_scenario(new GameScenario(this))
{
    setInitialSubState(m_runningState);

    m_runningState->pauseTrigger().setTarget(new TriggeredTransition(m_runningState, m_pausedState));
    m_pausedState->continueTrigger().setTarget(new TriggeredTransition(m_pausedState, m_runningState));
}

Game* GamePlay::game() {
    return m_game;
}

GamePlayScene& GamePlay::scene() {
    return *m_scene;
}

GamePlayRunning& GamePlay::running() {
    return *m_runningState;
}

GamePlayPaused& GamePlay::paused() {
    return *m_pausedState;
}

const Scene& GamePlay::scene() const {
    return *m_scene;
}

const CameraHead& GamePlay::cameraHead() const {
    return m_player->cameraHead();
}

Player& GamePlay::player() {
    return *m_player;
}

SoundManager& GamePlay::soundManager() {
    return *m_soundManager;
}

void GamePlay::loadScenario(int i) {
    m_scenario->clear();
    switch (i){
    case 0:
        m_scenario.reset(new GameScenario(this));
        break;
    case 1:
        m_scenario.reset(new BattleScenario(this));
        break;
    default:
        m_scenario.reset(new BaseScenario(this));
    }
    m_scenario->load();
}

void GamePlay::update(float deltaSec) {
    GameState::update(deltaSec);
    m_scene->update(deltaSec);
}

void GamePlay::onEntered() {
    GameState::onEntered();

    m_scenario->load();
}

void GamePlay::onLeft() {
    GameState::onLeft();
}

