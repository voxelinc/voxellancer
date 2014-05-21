#pragma once

#include <memory>
#include <string>

#include "scripting/scriptable.h"

#include "universe/functionalobject.h"


class MissionScript;

enum class MissionState {
    Idle,
    Running,
    Failed,
    Succeeded
};

class Mission : public FunctionalObject {
public:
    Mission(const std::string& path);
    virtual ~Mission();

    MissionState state() const;

    /**
     * Mark the mission as successfully played.
     * Calls onSuccess() in the script
     */
    void succeed();

    /**
     * Mark the mission as failed.
     * Calls onFailure() in the script
     */
    void fail();

    void update(float deltaSec);


protected:
    std::string m_scriptPath;
    glow::ref_ptr<MissionScript> m_script;
    MissionState m_state;

    void over();

    virtual bool doSpawn() override;
};

