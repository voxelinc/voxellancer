#include "gameplay.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/main/gameplaymain.h"
#include "gamestate/gameplay/paused/gameplaypaused.h"

#include "utils/fsm/trigger.h"
#include "utils/fsm/triggeredtransition.h"

#include "world/world.h"


GamePlay::GamePlay(Game* game):
    GameState("In Game", game),
    m_game(game),
    m_mainState(new GamePlayMain(this)),
    m_pausedState(new GamePlayPaused(this)),
    m_player(this),
    m_scene(this, &m_player),
    m_soundManager(new SoundManager()),
    m_scenario(this)
{
    setInitialSubstate(m_mainState);

    m_mainState->setPauseTrigger(Trigger<GameState>(new TriggeredTransition<GameState>(m_mainState, m_pausedState)));
    m_pausedState->setContinueTrigger(Trigger<GameState>(new TriggeredTransition<GameState>(m_pausedState, m_mainState)));
}

Game* GamePlay::game() {
    return m_game;
}

const Scene& GamePlay::scene() const {
    return m_scene;
}

const CameraHead& GamePlay::cameraHead() const {
    return m_player.cameraDolly().cameraHead();
}

Player& GamePlay::player() {
    return m_player;
}

SoundManager& GamePlay::soundManager() {
    return *m_soundManager;
}

void GamePlay::update(float deltaSec) {
    GameState::update(deltaSec);
    m_scene.update(deltaSec);
}

void GamePlay::onEntered() {
    GameState::onEntered();

    m_scenario.load();
}

void GamePlay::onLeft() {
    GameState::onLeft();
}

