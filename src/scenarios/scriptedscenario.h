#pragma once

#include <memory>
#include <string>

#include "scripting/script.h"

#include "basescenario.h"


class World;
class GamePlay;
class GamePlayScript;

class ScriptedScenario: public BaseScenario {
public:
    ScriptedScenario(GamePlay* gamePlay, const std::string& path);
    virtual ~ScriptedScenario();

    virtual void load() override;
    virtual void clear() override;

protected:
    std::shared_ptr<GamePlayScript> m_script;

    virtual void populateWorld() override;

    std::string m_path;
};

