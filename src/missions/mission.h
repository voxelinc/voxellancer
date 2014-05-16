#pragma once

#include <memory>
#include <string>

#include "scripting/scriptable.h"

#include "world/universeelement.h"


class MissionScript;
class World;

enum class MissionState {
    Idle,
    Running,
    Failed,
    Succeeded
};

class Mission : public UniverseElement {
public:
    Mission(const std::string& path);
    ~Mission();

    void start();

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

    virtual void spawn() override;


protected:
    void over();


protected:
    std::string m_scriptPath;
    std::shared_ptr<MissionScript> m_script;
    MissionState m_state;
};

