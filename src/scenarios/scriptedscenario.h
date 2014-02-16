#pragma once

#include <string>

#include "scripting/script.h"
#include "scripting/gameplayscript.h"

#include "basescenario.h"


class World;
class Game;

class ScriptedScenario: public BaseScenario {
public:
    ScriptedScenario(Game* game, const std::string& path);


protected:
    GamePlayScript m_script

    virtual void populateWorld() override;
};

