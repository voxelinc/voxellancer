#pragma once

#include <string>


/*
    Handle to a lua script
*/
class Script {
public:
    Script();
    Script(const std::string& name);

    void load(const std::string& name);
};

