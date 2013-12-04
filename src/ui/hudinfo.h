#pragma once

#include <string>

#include <glm/glm.hpp>



class HUDInfo  {
public:
	HUDInfo();

    std::string name();
    void setName(const std::string& name);

    bool showOnHud();
    void setShowOnHud(bool show);

protected:
    std::string m_name;
    bool m_showOnHud;

};
