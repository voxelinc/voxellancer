#pragma once

#include "gameplayscript.h"

class Mission;

class MissionScript : public GamePlayScript {
public:
    MissionScript(Mission& mission, ScriptEngine& scriptEngine);

    Mission& mission();

    virtual void update(float deltaSec) override;

    void onSuccess();
    void onFailure();


protected:
    Mission& m_mission;

    virtual void doSpawn() override;
    virtual void doUnspawn() override;
};

