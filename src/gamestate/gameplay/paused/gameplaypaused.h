#pragma once

#include "gamestate/gamestate.h"
#include "../gameplayfreecaminput.h"

#include "utils/statemachine/keytrigger.h"


class GamePlay;

class GamePlayPaused: public GameState {
public:
    GamePlayPaused(GamePlay* gamePlay);

    Trigger& continueTrigger();

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GamePlay* m_gamePlay;

    KeyTrigger m_continueTrigger;

    std::unique_ptr<GamePlayFreecamInput> m_input;
};

