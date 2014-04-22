#include "worldobjectinfo.h"

#include "equipment/shield.h"
#include "equipment/shieldslot.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"


WorldObjectInfo::WorldObjectInfo(WorldObject& worldObject):
    m_worldObject(worldObject),
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

std::string WorldObjectInfo::shieldStatus() {
    float shieldHP = 0;
    float shieldMaxHP = 0;

    for (std::shared_ptr<ShieldSlot>& shieldSlot : m_worldObject.components().shieldSlots()) {
        if (shieldSlot->shield()) {
            shieldHP += shieldSlot->shield()->hp();
            shieldMaxHP += shieldSlot->shield()->maxHP();
        }
    }

    if (shieldMaxHP > 0.0f) {
        int shieldPercent = static_cast<int>(shieldHP * 100 / shieldMaxHP);
        return std::to_string(shieldPercent);
    }

    return "-";
}

