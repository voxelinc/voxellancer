#pragma once

#include <memory>
#include <string>

#include "display/viewer.h"

#include "sound/soundmanager.h"

#include "utils/fsm/state.h"


/*
    Base class for a State the game can be in - for example
    Menu, OptionsMenu, normal Gameplay or ingame menu
*/
class GameState: public State<GameState> {
public:
    GameState(const std::string& name, GameState* parentGameState);

    GameState* parentGameState();

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GameState* m_parentGameState;
};

