#pragma once

#include <unordered_set>

#include <glm/glm.hpp>


class Sector;
class WorldTree;
class WorldObject;

class WorldTreeScanner {
public:
    WorldTreeScanner();
    virtual ~WorldTreeScanner();

    float scanInterval() const;
    void setScanInterval(float scanInterval);

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    const std::unordered_set<WorldObject*>& worldObjects();
    const std::unordered_set<WorldObject*>& foundWorldObjects();
    const std::unordered_set<WorldObject*>& lostWorldObjects();

    void update(float deltaSec, WorldObject* worldObject);
    void update(float deltaSec, Sector* sector, const glm::vec3& position);

    virtual void onFoundWorldObject(WorldObject* worldObject);
    virtual void onLostWorldObject(WorldObject* worldObject);


protected:
    float m_scanInterval;
    float m_scanCountdown;

    float m_scanRadius;

    std::unordered_set<WorldObject*> m_worldObjects;

    std::unordered_set<WorldObject*> m_foundWorldObjects;
    std::unordered_set<WorldObject*> m_lostWorldObjects;

    WorldObject* m_worldObject;
    Sector* m_sector;
    glm::vec3 m_position;


    void update(float deltaSec, WorldObject* worldObject, Sector* sector, const glm::vec3& position);
    void scan();
    std::unordered_set<WorldObject*> worldObjectsInRange();
};

