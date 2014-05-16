#include "gameplay.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "display/rendering/texturerenderer.h"
#include "display/viewer.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/running/gameplayrunning.h"
#include "gamestate/gameplay/paused/gameplaypaused.h"
#include "gamestate/gameplay/input/gameplaynormalinput.h"
#include "gamestate/gameplay/input/gameplayfreecaminput.h"
#include "gameplayscene.h"

#include "ui/hud/hud.h"

#include "universe/universe.h"

#include "utils/statemachine/trigger.h"
#include "utils/statemachine/triggeredtransition.h"

#include "scenarios/basescenario.h"

#include "sound/soundmanager.h"

#include "voxeleffect/voxelparticleengine.h"

#include "player.h"


GamePlay::GamePlay(Game* game) :
    GameState("In Game", game),
    m_game(game),
    m_universe(new Universe()),
    m_runningState(new GamePlayRunning(this)),
    m_pausedState(new GamePlayPaused(this)),
    m_normalInput(new GamePlayNormalInput(*this)),
    m_freecamInput(new GamePlayFreecamInput(*this)),
    m_freecamActive(false),
    m_scene(new GamePlayScene(*this)),
    m_soundManager(new SoundManager())
{
    updateView();
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

Universe& GamePlay::universe() {
    return *m_universe;
}

bool GamePlay::freecamActive() const {
    return m_freecamActive;
}

void GamePlay::setFreecamActive(bool active) {
    m_freecamActive = active;

    if (m_freecamActive) {
        m_freecamInput->setPosition(m_universe->player().cameraHead().cameraDolly()->position());
        m_freecamInput->setOrientation(m_universe->player().cameraHead().cameraDolly()->orientation());

        m_universe->player().move(glm::vec3(0));
        m_universe->player().rotate(glm::vec3(0));

        Property<bool>("vfx.drawhud").set(false);
    } else {
        Property<bool>("vfx.drawhud").set(true);
    }
}

const Scene& GamePlay::scene() const {
    return *m_scene;
}

const CameraHead& GamePlay::cameraHead() const {
    return m_freecamActive ? m_freecamInput->cameraHead() : m_universe->player().cameraHead();
}

InputHandler& GamePlay::inputHandler() {
    if (m_freecamActive) {
        return *m_freecamInput.get();
    } else {
        return *m_normalInput.get();
    }
}

SoundManager& GamePlay::soundManager() {
    return *m_soundManager;
}

void GamePlay::loadScenario(int i) {
    TextureRenderer loadRenderer("data/textures/loading.dds");
    loadRenderer.display("Loading Scenario...");

    m_soundManager->stopAll();
    updateView();

    switch (i) {
    default:
        m_scenario.reset(new BaseScenario(m_universe.get()));
    }

    m_scenario->load();
}

void GamePlay::update(float deltaSec) {
    inputHandler().update(deltaSec);

    if (m_freecamActive) {
        m_soundManager->setListener(m_freecamInput->cameraHead().position(), m_freecamInput->cameraHead().orientation());
    } else {
        m_soundManager->setListener(m_universe->player().cameraHead().position(), m_universe->player().cameraHead().orientation());
    }

    GameState::update(deltaSec);
    m_scene->update(deltaSec);
}

void GamePlay::onEntered() {
    GameState::onEntered();
    m_soundManager->activate();

    loadScenario(0);
}

void GamePlay::onLeft() {
    m_soundManager->deactivate();

    GameState::onLeft();
}

void GamePlay::updateView() {
    m_universe->player().hud().setView(&m_game->viewer().view());
}

