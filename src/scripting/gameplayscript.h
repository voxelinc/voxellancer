#pragma once

#include <map>
#include <memory>

#include "scripting/script.h"


class ScriptEngine;
class Ship;
class Squad;

class GamePlayScript: public Script {
public:
    GamePlayScript(ScriptEngine* scriptEngine);

    virtual void load(const std::string& path) override;


protected:
    ScriptEngine* m_scriptEngine;

    int m_shipHandleIncrementor;
    std::map<int, Ship*> m_shipHandles;

    int m_squadHandleIncrementor;
    std::map<int, std::shared_ptr<Squad>> m_squadHandles;


    int apiCreateShip(std::string name);
    int apiSpawnShip(int handle);
    int apiSetPosition(int handle, float x, float y, float z);
    int apiCreateSingleShotTimer(std::string function, float delta);
    int apiCreateLoopingTimer(std::string function, float delta);
};

