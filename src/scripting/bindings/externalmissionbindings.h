#pragma once

#include <string>

#include "bindings.h"


/**
    API to manage missions from the outside
*/
class ExternalMissionBindings : public Bindings {
public:
    ExternalMissionBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    apikey apiMissionStart(const std::string& name);
};

