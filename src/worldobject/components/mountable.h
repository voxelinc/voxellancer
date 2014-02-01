#pragma once

#include <map>


/*
    Baseclass for slot-like entities that can be
    mounted by a set of names
*/
class Mountable {
public:
    bool mountable(const std::string& name) const;
    void setMountable(const std::string& name, bool mountable);


protected:
    std::map<std::string, bool> m_mountables;
};
