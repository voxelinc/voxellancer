#include "character.h"

#include "ai/aigrouptask.h"
#include "ai/aitask.h"
#include "ai/squad.h"
#include "ai/squadlogic.h"

#include "worldobject/ship.h"
#include "equipment/weapons/bullet.h"
#include "equipment/weapons/rocket.h"

#include "player.h"

#include "factions/faction.h"
#include "factions/factionrelation.h"
#include "factions/factionmatrix.h"

#include "ui/hud/hud.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"


Character::Character(Ship& ship, Faction& faction):
    m_ship(ship),
    m_faction(&faction),
    m_task(nullptr),
    m_world(World::instance())
{
}

Faction& Character::faction() {
    return *m_faction;
}

void Character::setFaction(Faction& faction) {
    m_faction = &faction;
}

void Character::setTask(std::shared_ptr<AiTask> task) {
    m_task = task;
}

std::shared_ptr<AiTask> Character::task() {
    return m_task;
}

void Character::update(float deltaSec) {
    if (m_ship.squadLogic()->isSquadLeader() && m_ship.squadLogic()->squad()->task().get()) {
        m_ship.squadLogic()->squad()->task()->update(deltaSec);
    }
    if (m_task.get()) {
        m_task->update(deltaSec);
    }
    resetFriendliness(deltaSec);
}

void Character::onCollisionWith(WorldObject* worldObject) {
    float relationModifier = 0;
    std::string warningMessage;
    WorldObject* aggressor;
    switch (worldObject->objectType()) {
        case WorldObjectType::Ship: {
            Ship* ship = static_cast<Ship*>(worldObject);
            aggressor = ship;
            relationModifier = -0.5f;
            warningMessage = m_ship.info().name() + ": Watch where you're going!";
        }
            break;
        case WorldObjectType::Bullet: {
            Bullet* bullet = static_cast<Bullet*>(worldObject);
            aggressor = bullet->creator();
            relationModifier = -1;
            warningMessage = m_ship.info().name() + ": Check your fire!";
        }
            break;
        case WorldObjectType::Rocket:{
            Rocket* rocket = static_cast<Rocket*>(worldObject);
            aggressor = rocket->creator();
            relationModifier = -1;
            warningMessage = m_ship.info().name() + ": Check your fire!";
        }
            break;
    }
    if (aggressor != m_world->player().ship()) {
        return;
    } else {
        if (relationTypeTo(aggressor) != FactionRelationType::Enemy) {
            m_world->player().hud().showMessage(warningMessage);
        }
    }
    onAggressionBy(aggressor, relationModifier);
}

void Character::onAggressionBy(WorldObject* aggressor, float relationModifier) {
    if (aggressor->objectType() != WorldObjectType::Ship) {
        return;
    }
    Ship* ship = static_cast<Ship*>(aggressor);
    float friendlinessToAggressorFaction = m_faction->relationTo(ship->character()->faction()).friendliness();
    relationModifier *= 2.0f - glm::abs(friendlinessToAggressorFaction) / 100.0f;
    changeFriendlinessToAggressor(ship, relationModifier);
}

void Character::onKilledBy(WorldObject* worldObject) {
    if (worldObject->objectType() != WorldObjectType::Ship) {
        return;
    }
    Ship* ship = static_cast<Ship*>(worldObject);
    if (ship != m_world->player().ship()) {
        return;
    }
    m_faction->changeFriendlinessToFaction(ship->character()->faction(), -10);
    if (m_ship.squadLogic()->squad()) {
        m_ship.squadLogic()->squad()->propagadeFriendlinessToWorldObject(ship, glm::min(-30.0f, m_faction->relationTo(ship->character()->faction()).friendliness()));
    }
}

FactionRelationType Character::relationTypeTo(WorldObject* worldObject) {
    if (m_friendlinessToWorldObject.count(makeHandle(worldObject)) > 0) {
        return FactionRelation::type(m_friendlinessToWorldObject[makeHandle(worldObject)]);
    }
    if (worldObject->objectType() != WorldObjectType::Ship) {
        return FactionRelationType::Neutral;
    }
    return m_faction->relationTo(static_cast<Ship*>(worldObject)->character()->faction()).type();
}

void Character::setFriendlinessToWorldObject(WorldObject* worldObject, float friendliness) {
    m_friendlinessToWorldObject[makeHandle(worldObject)] = friendliness;
    m_friendlinessResetDelay[makeHandle(worldObject)] = 10.0f;
}

void Character::changeFriendlinessToAggressor(WorldObject* aggressor, float difference) {
    if (aggressor->objectType() != WorldObjectType::Ship) {
        return;
    }
    Ship* ship = static_cast<Ship*>(aggressor);
    float friendliness = m_friendlinessToWorldObject[makeHandle(aggressor)];
    if (friendliness == 0.0f) {
        friendliness = m_faction->relationTo(ship->character()->faction()).friendliness();
    }
    friendliness += difference;
    if (FactionRelation::type(friendliness) == FactionRelationType::Enemy && m_ship.squadLogic()->squad().get()) {
        m_ship.squadLogic()->squad()->propagadeFriendlinessToWorldObject(aggressor, friendliness);
    }
    m_world->factionMatrix().changeFriendlinessToFaction(*m_faction, ship->character()->faction(), difference / 10.0f);
    setFriendlinessToWorldObject(aggressor, friendliness);
}

void Character::resetFriendliness(float deltaSec) {
    for (auto it = m_friendlinessToWorldObject.begin(); it != m_friendlinessToWorldObject.end();) {
        float friendliness = it->second;
        if (!it->first.valid()) {
            it = m_friendlinessToWorldObject.erase(it);
            continue;
        }
        if (it->first->objectType() != WorldObjectType::Ship) {
            it = m_friendlinessToWorldObject.erase(it);
            continue;
        }
        const Ship* ship = static_cast<const Ship*>(it->first.get());
        if (m_friendlinessResetDelay.count(it->first) > 0) {
            if (m_friendlinessResetDelay[it->first] > 0) {
                m_friendlinessResetDelay[it->first] -= deltaSec;
                it++;
                continue;
            } else {
                m_friendlinessResetDelay.erase(it->first);
            }
        }
        if (m_faction->relationTo(ship->character()->faction()).friendliness() > friendliness) {
            it->second += deltaSec;
        } else {
            it->second -= deltaSec;
        }
        if (glm::abs(m_faction->relationTo(ship->character()->faction()).friendliness() - it->second) < 0.1f) {
            it = m_friendlinessToWorldObject.erase(it);
        } else {
            it++;
        }
    }
}
