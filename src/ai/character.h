#pragma once

#include <memory>

#include "factions/factionrelation.h"


class AiTask;
class Faction;
class Ship;
class WorldObject;
class World;

/**
 *  The Character is the Ship's pilot and executes his AiTask. He has a Faction which decides
 *  who is a friend or foe to him
 */

class Character {
public:
    Character(Ship& ship, Faction& faction);

    Faction& faction();
    void setFaction(Faction& faction);

    void setTask(std::shared_ptr<AiTask> task);
    std::shared_ptr<AiTask> task();

    virtual void update(float deltaSec);

    void onCollisionWith(WorldObject* worldObject);

    void onKilledBy(WorldObject* worldObject);

    FactionRelationType relationTypeToPlayer();

    FactionRelationType relationTypeTo(Faction& other);

    void setFriendlinessToPlayer(float friendliness);

protected:
    World* m_world;
    Ship& m_ship;
    Faction* m_faction;
    std::shared_ptr<AiTask> m_task;
    float m_friendlinessToPlayer;
    void changeFriendlinessToPlayer(float difference);
};

