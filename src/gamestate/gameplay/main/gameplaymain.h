#pragma once

#include "gamestate/gamestate.h"

#include "sound/soundmanager.h"

#include "utils/fsm/trigger.h"

#include "gameplaymaininput.h"



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

