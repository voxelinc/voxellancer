#pragma once

#include <memory>
#include <string>

#include "scripting/scriptable.h"

#include "world/worldelement.h"


class MissionScript;
class World;

enum class MissionState {
    Idle,
    Running,
    Failed,
    Succeeded
};

class Mission : public WorldElement {
public:
    Mission(World* world, const std::string& path);
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
    void over();


protected:
    std::shared_ptr<MissionScript> m_script;
    MissionState m_state;
};

