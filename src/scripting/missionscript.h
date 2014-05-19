#pragma once

#include "gameplayscript.h"

class Mission;

class MissionScript : public GamePlayScript {
public:
    MissionScript(Mission& mission, ScriptEngine& scriptEngine);

    Mission& mission();

    void onSuccess();
    void onFailure();


protected:
    Mission& m_mission;

    virtual void doSpawn() override;
};

