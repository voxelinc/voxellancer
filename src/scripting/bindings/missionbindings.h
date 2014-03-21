#pragma once

#include "bindings.h"


class MissionScript;

class MissionBindings : public Bindings {
public:
    MissionBindings(MissionScript& script);


protected:
    MissionScript& m_missionScript;


    virtual void bind();

    int apiMissionSucceeded();
    int apiMissionFailed();
    int apiMissionMessage(const std::string& message);
    int apiMissionFailureMessage(const std::string& message);
    int apiMissionSuccessMessage(const std::string& message);
};

