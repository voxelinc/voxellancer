#pragma once

#include <string>


class Engine;

/*
    Dedicated to load either a GenericEngine from a given property-prefix
    or - if any is known by that name - a special engine that has its own
    non-generic implementation
*/
class EngineBuilder {
public:
    EngineBuilder(const std::string& name);

    Engine* build();


protected:
    std::string m_name;
};

