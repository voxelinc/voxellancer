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
    m_friendlinessToPlayer = m_world->factionMatrix().getRelationToPlayer(*m_faction).friendliness();
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
    std::string warningMessage;
    switch (worldObject->objectType()) {
        case WorldObjectType::Ship: {
            Ship* ship = static_cast<Ship*>(worldObject);
            if (ship == m_world->player().ship()) {
                relationModifier = -0.5f;
                warningMessage = m_ship.info().name() + ": Watch where you're going!";
            }
        }
            break;
        case WorldObjectType::Bullet: {
            Bullet* bullet = static_cast<Bullet*>(worldObject);
            if (bullet->creator() == m_world->player().ship()) {
                relationModifier = -1;
                warningMessage = m_ship.info().name() + ": Check your fire!";
            }
        }
            break;
        case WorldObjectType::Rocket:{
            Rocket* rocket = static_cast<Rocket*>(worldObject);
            if (rocket->creator() == m_world->player().ship()) {
                relationModifier = -1;
                warningMessage = m_ship.info().name() + ": Check your fire!";
            }
        }
            break;
    }
    if (relationModifier != 0) {
        float friendliness = m_faction->relationTo(m_world->factionMatrix().getFaction("player")).friendliness();
        relationModifier *= 2.0f - glm::abs(friendliness) / 100.0f;
        changeFriendlinessToPlayer(relationModifier);
    }
    if (m_friendlinessToPlayer > -30.0f) {
        m_world->player().hud().showCommunicationMessage(warningMessage);
    }
}

void Character::onKilledBy(WorldObject* worldObject) {
    if (worldObject == m_world->player().ship()) {
        m_world->factionMatrix().changeFriedlinessToPlayer(*m_faction, -10);
        if (m_ship.squadLogic()->squad()) {
            m_ship.squadLogic()->squad()->propagadeFriendlinessToPlayer(glm::min(-30.0f, m_world->factionMatrix().getRelationToPlayer(*m_faction).friendliness()));
        }
    }
}

FactionRelationType Character::relationTypeToPlayer() {
    float friendliness = glm::min(m_friendlinessToPlayer, m_world->factionMatrix().getRelationToPlayer(*m_faction).friendliness());
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
    m_world->factionMatrix().changeFriedlinessToPlayer(*m_faction, difference / 10.0f);
}

void Character::setFriendlinessToPlayer(float friendliness) {
    m_friendlinessToPlayer = friendliness;
}
