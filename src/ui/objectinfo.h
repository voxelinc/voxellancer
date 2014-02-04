#pragma once

#include <string>

#include <glm/glm.hpp>

class ObjectInfo  {
public:
    ObjectInfo();

    std::string name();
    void setName(const std::string& name);

    bool showOnHud();
    void setShowOnHud(bool show);

    bool canLockOn();
    void setCanLockOn(bool canLockOn);


protected:
    std::string m_name;
    bool m_showOnHud;
    bool m_canLockOn;
};

