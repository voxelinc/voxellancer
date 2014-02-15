#pragma once

#include "sound/soundmanager.h"

#include "utils/fsm/trigger.h"

#include "ui/gameplaymaininput.h"

#include "gamestate.h"


class GamePlay;

class GamePlayMain: public GameState {
public:
    GamePlayMain(GamePlay* gamePlay);

    GamePlayMainInput& inputHandler();

    void setPauseTrigger(const Trigger<GameState>& pauseTrigger);

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GamePlay* m_gamePlay;

    GamePlayMainInput m_inputHandler;
};

