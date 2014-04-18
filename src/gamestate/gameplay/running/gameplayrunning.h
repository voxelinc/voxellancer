#pragma once

#include <memory>

#include "gamestate/gamestate.h"

#include "utils/statemachine/keytrigger.h"


class GamePlay;
class GamePlayNormalInput;

class GamePlayRunning: public GameState {
public:
    GamePlayRunning(GamePlay* gamePlay);

    Trigger& pauseTrigger();

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GamePlay* m_gamePlay;
    KeyTrigger m_pauseTrigger;

    std::unique_ptr<GamePlayNormalInput> m_input;
};

