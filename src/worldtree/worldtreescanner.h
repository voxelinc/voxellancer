#pragma once

#include <list>

#include <glm/glm.hpp>


class WorldTree;
class WorldObject;

class WorldTreeScanner {
public:
    WorldTreeScanner(WorldTree* worldTree);

    float scanInterval() const;
    void setScanInterval(float scanInterval);

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    std::list<WorldObject*> worldObjects();

    std::list<WorldObject*> foundWorldObjects();
    std::list<WorldObject*> lostWorldObjects();

    void update(float deltaSec, WorldObject* worldObject);
    void update(float deltaSec, const glm::vec3& position);

    virtual void onFoundWorldObject(WorldObject* worldObject);
    virtual void onLostWorldObject(WorldObject* worldObject);


protected:
    WorldTree* m_worldTree;
    WorldObject* m_worldObject;

    float m_scanInterval;
    float m_scanCountdown;

    float m_scanRadius;

    std::list<WorldObject*> m_worldObjects;

    std::list<WorldObject*> m_foundWorldObjects;
    std::list<WorldObject*> m_lostWorldObjects;


    void update(float deltaSec, WorldObject* worldObject, const glm::vec3& position);
    void scan(WorldObject* worldObject, const glm::vec3& position);
    void callHooks();
};

