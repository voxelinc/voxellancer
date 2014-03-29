#pragma once

#include <memory>
#include <string>

#include "utils/statemachine/state.h"

class CameraHead;
class Scene;

/**
*    Base class for a State the game can be in - for example
*    Menu, OptionsMenu, normal Gameplay or ingame menu
*
*    A GameState has to provide a Scene and a CameraHead so
*    that it can be displayed by the Viewer of Game. Per default
*    these 2 return their parents Scene and CameraHead so that GameStates
*    can be arbirtarily nested
*/
class GameState: public State {
public:
    GameState(const std::string& name, GameState* parent);

    GameState* parentGameState();

    virtual const Scene& scene() const;
    virtual const CameraHead& cameraHead() const;

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    GameState* m_parentGameState;
};

