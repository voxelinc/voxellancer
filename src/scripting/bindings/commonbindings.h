#pragma once

#include <string>

#include <glm/glm.hpp>

#include "bindings.h"


class CommonBindings : public Bindings {
public:
    CommonBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    bool apiValid(apikey key);
    int apiShowMessage(const std::string& string);
    int apiPlayVoice(const std::string& soundFile);

    int apiSetEventActive(apikey eventPoll, bool active);

    apikey apiCreateSingleShotTimer(const std::string& callback, float delta);
    apikey apiCreateLoopingTimer(const std::string& callback, float delta);
};

