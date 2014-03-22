#pragma once

#include <memory>
#include <string>

#include "scripting/scriptable.h"


class MissionScript;

class Mission : public Scriptable {
public:
    Mission(const std::string& path);
    ~Mission();

    void start();

    bool active() const;
    bool succeeded() const;

    /*
        Mark the mission as successfully played.
        Calls onSuccess() in the script
    */
    void succeed();

    /*
        Mark the mission the function as failure played.
        Calls onFailure() in the script
    */
    void fail();

    /*
        Mark the mission as inactive, deactivate the script
    */
    void over();

    const std::string& title() const;
    const std::string& caption() const;
    const std::string& briefing() const;

    void update(float deltaSec);



protected:
    std::shared_ptr<MissionScript> m_script;
    bool m_active;
    bool m_succeeded;
};

