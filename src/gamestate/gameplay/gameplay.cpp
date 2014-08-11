#include "gameplay.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/running/gameplayrunning.h"
#include "gamestate/gameplay/paused/gameplaypaused.h"
#include "gamestate/gameplay/input/gameplaynormalinput.h"
#include "gamestate/gameplay/input/gameplayfreecaminput.h"
#include "gameplayscene.h"

#include "utils/statemachine/trigger.h"
#include "utils/statemachine/triggeredtransition.h"

#include "scenarios/basescenario.h"
#include "scenarios/battlescenario.h"
#include "scenarios/gamescenario.h"
#include "scenarios/frozengamescenario.h"
#include "scenarios/friendlyfirescenario.h"
#include "scenarios/missionscenario.h"
#include "scenarios/scriptedscenario.h"
#include "scenarios/piratescenario.h"

#include "sound/soundmanager.h"

#include "voxeleffect/voxelparticleengine.h"

#include "world/world.h"

#include "player.h"
#include "camera/camerahead.h"
#include "camera/cameradolly.h"
#include "ui/hud/hud.h"
#include "ui/hud/buttonhudget.h"
#include "display/viewer.h"

#include "display/rendering/texturerenderer.h"


GamePlay::GamePlay(Game* game) :
    GameState("In Game", game),
    m_game(game),
    m_runningState(new GamePlayRunning(this)),
    m_pausedState(new GamePlayPaused(this)),
    m_normalInput(new GamePlayNormalInput(*this)),
    m_freecamInput(new GamePlayFreecamInput(*this)),
    m_freecamActive(false),
    m_scene(new GamePlayScene(*this)),
    m_scenario(new ScriptedScenario(this, "")),
    m_soundManager(new SoundManager())
{
    setResetCallback();
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

bool GamePlay::freecamActive() const {
    return m_freecamActive;
}

void GamePlay::setFreecamActive(bool active) {
    m_freecamActive = active;

    if (m_freecamActive) {
        m_freecamInput->setPosition(World::instance()->player().cameraHead().cameraDolly()->position());
        m_freecamInput->setOrientation(World::instance()->player().cameraHead().cameraDolly()->orientation());

        World::instance()->player().move(glm::vec3(0));
        World::instance()->player().rotate(glm::vec3(0));

        Property<bool>("vfx.drawhud").set(false);
    } else {
        Property<bool>("vfx.drawhud").set(true);
    }
}

const Scene& GamePlay::scene() const {
    return *m_scene;
}

const CameraHead& GamePlay::cameraHead() const {
    return m_freecamActive ? m_freecamInput->cameraHead() : World::instance()->player().cameraHead();
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
    displayLoadingScreen("Loading Scenario...");

    clearScenario();

    switch (i) {
    case 0:
        m_scenario.reset(new ScriptedScenario(this, "data/scripts/scenarios/demo.lua"));
        break;
    case 1:
        m_scenario.reset(new GameScenario(this));
        break;
    case 2:
        m_scenario.reset(new BattleScenario(this));
        break;
    case 3:
        m_scenario.reset(new FrozenGameScenario(this));
        break;
    case 4:
        m_scenario.reset(new PirateScenario(this));
        break;
    case 5:
        m_scenario.reset(new FriendlyFireScenario(this));
        break;
    default:
        m_scenario.reset(new BaseScenario(this));
    }

    m_scenario->load();
    setResetCallback();

}

void GamePlay::update(float deltaSec) {
    inputHandler().update(deltaSec);

    if (m_freecamActive) {
        m_soundManager->setListener(m_freecamInput->cameraHead().position(), m_freecamInput->cameraHead().orientation());
    } else {
        m_soundManager->setListener(World::instance()->player().cameraHead().position(), World::instance()->player().cameraHead().orientation());
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
    World::instance()->player().hud().setView(&m_game->viewer().view());
}

void GamePlay::resetScenario() {
    displayLoadingScreen("resetting scenario");
    clearScenario();

    m_scenario->load();
}

void GamePlay::clearScenario() {
    m_soundManager->stopAll();
    m_scenario->clear();
    updateView();
}

void GamePlay::displayLoadingScreen(const std::string& status) {
    TextureRenderer loadRenderer("data/textures/loading.dds");
    loadRenderer.display(status);
}

void GamePlay::resetButtonCallback(ClickType clickType){
    resetScenario();
    setResetCallback();
}

void GamePlay::setResetCallback() {
    World::instance()->player().hud().resetButton()->setCallback((std::function<void(ClickType clickType)>)std::bind(&GamePlay::resetButtonCallback, this, std::placeholders::_1));
}
