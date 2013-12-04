#include "hudinfo.h"

HUDInfo::HUDInfo() :
m_name("Cluster"),
m_showOnHud(true)
{
}

std::string HUDInfo::name(){
    return m_name;
}

void HUDInfo::setName(const std::string& name){
    m_name = name;
}

bool HUDInfo::showOnHud(){
    return m_showOnHud;
}

void HUDInfo::setShowOnHud(bool show){
    m_showOnHud = show;
}