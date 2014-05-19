#pragma once

#include <memory>
#include <unordered_map>

#include "factions/factionrelation.h"
#include "utils/handle/handle.h"
#include "utils/handle/handlehash.h"


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

    void onAggressionBy(WorldObject* aggressor, float friendlinessModifier);

    FactionRelationType relationTypeTo(Faction& other);
    FactionRelationType relationTypeTo(WorldObject* worldObject);

    void setFriendlinessToWorldObject(WorldObject* worldObject, float friendliness);

protected:
    World* m_world;
    Ship& m_ship;
    Faction* m_faction;
    std::shared_ptr<AiTask> m_task;

    void resetFriendliness(float deltaSec);
    std::unordered_map<Handle<WorldObject>, float> m_friendlinessToWorldObject;
    void changeFriendlinessToAggressor(WorldObject* aggressor, float difference);
};

