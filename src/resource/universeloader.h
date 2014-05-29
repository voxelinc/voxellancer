#pragma once

#include <string>


class UniverseLoader {
public:
    UniverseLoader(const std::string& path);

    Universe* load();

protected:
    std::string m_path;
};

