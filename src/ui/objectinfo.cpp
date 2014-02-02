#include "objectinfo.h"

ObjectInfo::ObjectInfo() :
    m_name("Object"),
    m_showOnHud(false),
    m_canLockOn(false)
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

