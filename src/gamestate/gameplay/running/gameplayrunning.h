#pragma once

#include <memory>

#include "gamestate/gamestate.h"

#include "sound/soundmanager.h"

#include "utils/fsm/trigger.h"




class GamePlay;
class GamePlayRunningInput;

class GamePlayRunning: public GameState {
public:
    GamePlayRunning(GamePlay* gamePlay);

    GamePlayRunningInput& input();

    void setPauseTrigger(const Trigger<GameState>& pauseTrigger);

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GamePlay* m_gamePlay;

    std::unique_ptr<GamePlayRunningInput> m_input;
};

