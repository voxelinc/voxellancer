#pragma once

#include <set>

#include <glm/glm.hpp>


class WorldTree;
class WorldObject;

class WorldTreeScanner {
public:
    WorldTreeScanner();

    float scanInterval() const;
    void setScanInterval(float scanInterval);

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    const std::set<WorldObject*>& worldObjects();
    const std::set<WorldObject*>& foundWorldObjects();
    const std::set<WorldObject*>& lostWorldObjects();

    void update(float deltaSec, WorldObject* worldObject);
    void update(float deltaSec, const glm::vec3& position);

    virtual void onFoundWorldObject(WorldObject* worldObject);
    virtual void onLostWorldObject(WorldObject* worldObject);


protected:
    float m_scanInterval;
    float m_scanCountdown;

    float m_scanRadius;

    std::set<WorldObject*> m_worldObjects;

    std::set<WorldObject*> m_foundWorldObjects;
    std::set<WorldObject*> m_lostWorldObjects;


    void update(float deltaSec, WorldObject* worldObject, const glm::vec3& position);
    void scan(WorldObject* worldObject, const glm::vec3& position);
    std::set<WorldObject*> worldObjectsInRange(WorldObject* worldObject, const glm::vec3& position);
};

