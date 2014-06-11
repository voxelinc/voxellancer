#pragma once

#include <string>


class Shield;

class ShieldBuilder {
public:
    ShieldBuilder(const std::string& name);

    Shield* build();


protected:
    std::string m_name;
};

