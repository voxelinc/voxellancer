#include "ingame.h"

#include "world/world.h"

#include "game.h"


InGame::InGame(Game* game):
    GameState("In Game", game),
    m_game(game),
    m_player(this),
    m_inputHandler(&m_player),
    m_scene(this, &m_player),
    m_scenario(this),
    m_soundManager(new SoundManager())
{
}

Game* InGame::game() {
    return m_game;
}

InGameScene& InGame::scene() {
    return m_scene;
}

InputHandler& InGame::inputHandler() {
    return m_inputHandler;
}

Player& InGame::player() {
    return m_player;
}

void InGame::update(float deltaSec) {
    GameState::update(deltaSec);

    World::instance()->update(deltaSec);
    m_player.update(deltaSec);
    m_inputHandler.update(deltaSec);

    m_soundManager->setListener(m_player.cameraPosition(), m_player.cameraOrientation());
}

void InGame::onEntered() {
    GameState::onEntered();

    m_inputHandler.setHMD(m_game->hmdManager().hmd());
    m_soundManager->activate();

    m_game->viewer().setScene(&m_scene);
    m_game->viewer().setCameraHead(&m_player.cameraDolly().cameraHead());

    m_scenario.load();
}

void InGame::onLeft() {
    m_soundManager->deactivate();

    GameState::onLeft();
}

