#pragma once

#include <string>

#include <glm/glm.hpp>

#include "bindings.h"

class CommonBindings : public Bindings {
public:
    CommonBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    bool apiValid(apikey key);
    int apiShowText(const std::string& string);
    int apiShowTextFor(const std::string& string, int seconds);

    int apiSetEventActive(apikey eventPoll, bool active);

    apikey apiCreateSingleShotTimer(const std::string& callback, float delta);
    apikey apiCreateLoopingTimer(const std::string& callback, float delta);

    apikey apiOnAABBEntered(apikey worldObject, glm::vec3 llf, glm::vec3 urb, const std::string& callback);
};
