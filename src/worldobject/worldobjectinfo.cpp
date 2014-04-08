#include "worldobjectinfo.h"

WorldObjectInfo::WorldObjectInfo() :
    m_name("Object"),
    m_showOnHud(false),
    m_canLockOn(false)
{
}

std::string WorldObjectInfo::name(){
    return m_name;
}

void WorldObjectInfo::setName(const std::string& name){
    m_name = name;
}

bool WorldObjectInfo::showOnHud(){
    return m_showOnHud;
}

void WorldObjectInfo::setShowOnHud(bool show){
    m_showOnHud = show;
}

bool WorldObjectInfo::canLockOn(){
    return  m_canLockOn;
}

void WorldObjectInfo::setCanLockOn(bool canLockOn){
    m_canLockOn = canLockOn;
}

