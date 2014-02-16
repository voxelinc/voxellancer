#pragma once

#include <memory>
#include <string>

#include "scripting/script.h"

#include "basescenario.h"


class World;
class Game;
class GamePlayScript;

class ScriptedScenario: public BaseScenario {
public:
    ScriptedScenario(Game* game, const std::string& path);
    ~ScriptedScenario();


protected:
    std::unique_ptr<GamePlayScript> m_script;

    virtual void populateWorld() override;
};

