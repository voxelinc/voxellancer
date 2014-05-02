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
#include "factions/factionRelation.h"
#include "factions/factionMatrix.h"

#include "world/world.h"


Character::Character(Ship& ship, Faction& faction):
    m_ship(ship),
    m_faction(&faction),
    m_task(nullptr)
{
    m_friendlinessToPlayer = World::instance()->factionMatrix().getRelationToPlayer(*m_faction).friendliness();
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
}

void Character::onCollisionWith(WorldObject* worldObject) {
    float relationModifier = 0;
    switch (worldObject->objectType()) {
        case WorldObjectType::Ship: {
            Ship* ship = static_cast<Ship*>(worldObject);
            if (ship == World::instance()->player().ship()) {
                relationModifier = -0.5f;
            }
        }
            break;
        case WorldObjectType::Bullet: {
            Bullet* bullet = static_cast<Bullet*>(worldObject);
            if (bullet->creator() == World::instance()->player().ship()) {
                relationModifier = -1;
            }
        }
            break;
        case WorldObjectType::Rocket:{
            Rocket* rocket = static_cast<Rocket*>(worldObject);
            if (rocket->creator() == World::instance()->player().ship()) {
                relationModifier = -1;
            }
        }
            break;
    }
    if (relationModifier != 0) {
        float friendliness = m_faction->relationTo(World::instance()->factionMatrix().getFaction("player")).friendliness();
        relationModifier *= 2.0f - glm::abs(friendliness) / 100.0f;
        changeFriendlinessToPlayer(relationModifier);
    }
}

void Character::onKilledBy(WorldObject* worldObject) {
    if (worldObject == World::instance()->player().ship()) {
        World::instance()->factionMatrix().changeFriedlinessToPlayer(*m_faction, -10);
        m_ship.squadLogic()->squad()->propagadeFriendlinessToPlayer(-30);
    }
}

FactionRelationType Character::relationTypeToPlayer() {
    float friendliness = glm::min(m_friendlinessToPlayer, World::instance()->factionMatrix().getRelationToPlayer(*m_faction).friendliness());
    return FactionRelation::type(friendliness);
}

FactionRelationType Character::relationTypeTo(Faction& other) {
    if (other.key() == "player") {
        return relationTypeToPlayer();
    }
    return m_faction->relationTo(other).type();
}

void Character::changeFriendlinessToPlayer(float difference) {
    m_friendlinessToPlayer += difference;
    if (FactionRelation::type(m_friendlinessToPlayer) == FactionRelationType::Enemy && m_ship.squadLogic()->squad().get()) {
        m_ship.squadLogic()->squad()->propagadeFriendlinessToPlayer(m_friendlinessToPlayer);
    }
    World::instance()->factionMatrix().changeFriedlinessToPlayer(*m_faction, difference / 10.0f);
}

void Character::setFriendlinessToPlayer(float friendliness) {
    m_friendlinessToPlayer = friendliness;
}
