#pragma once

#include "gamestate/gamestate.h"

#include "utils/fsm/trigger.h"

#include "gamestate/gameplay/running/gameplayrunning.h"



class GamePlay;

class GamePlayPaused: public GameState {
public:
    GamePlayPaused(GamePlay* gamePlay);

    void setContinueTrigger(const Trigger<GameState>& continueTrigger);

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GamePlay* m_gamePlay;

    Trigger<GameState> m_continueTrigger;
};

