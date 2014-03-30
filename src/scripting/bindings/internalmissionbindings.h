#pragma once

#include "bindings.h"


class MissionScript;

/**
    API available to MissionScript
*/
class InternalMissionBindings : public Bindings {
public:
    InternalMissionBindings(MissionScript& script);


protected:
    MissionScript& m_missionScript;


    virtual void bind() override;

    int apiMissionSucceed();
    int apiMissionFail();
    int apiMissionMessage(const std::string& message);
    int apiMissionFailureMessage(const std::string& message);
    int apiMissionSuccessMessage(const std::string& message);
};

