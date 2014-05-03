#pragma once

#include <memory>
#include <string>

#include "utils/handle/handleowner.h"

#include "scripting/scriptable.h"


class MissionScript;

enum class MissionState {
    Idle,
    Running,
    Failed,
    Succeeded
};

class Mission : public Scriptable, public HandleOwner {
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


protected:
    std::shared_ptr<MissionScript> m_script;
    MissionState m_state;
};

