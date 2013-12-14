#include "objectinfo.h"

ObjectInfo::ObjectInfo() :
    m_name("Cluster"),
    m_showOnHud(true),
    m_canLockOn(true)
{
}

std::string ObjectInfo::name(){
    return m_name;
}

void ObjectInfo::setName(const std::string& name){
    m_name = name;
}

bool ObjectInfo::showOnHud(){
    return m_showOnHud;
}

void ObjectInfo::setShowOnHud(bool show){
    m_showOnHud = show;
}

bool ObjectInfo::canLockOn(){
    return  m_canLockOn;
}

void ObjectInfo::setCanLockOn(bool canLockOn){
    m_canLockOn = canLockOn;
}
