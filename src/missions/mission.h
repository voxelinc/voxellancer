#pragma once

#include <memory>
#include <string>


class MissionScript;

class Mission {
public:
    Mission(const std::string& path);
    ~Mission();

    void start();

    bool active() const;

    /*
        Mark the mission as successfully played.
        Calls onSuccess() in the script
    */
    void succeeded();

    /*
        Mark the mission the function as failure played.
        Calls onFailure() in the script
    */
    void failed();

    const std::string& title() const;
    const std::string& caption() const;
    const std::string& briefing() const;

    void update(float deltaSec);



protected:
    std::shared_ptr<MissionScript> m_script;
    bool m_active;
};

