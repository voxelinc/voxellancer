#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>


class CollisionFilter;
class WorldTree;
class WorldObject;

class WorldTreeScanner {
public:
    WorldTreeScanner();
    ~WorldTreeScanner();

    float scanInterval() const;
    void setScanInterval(float scanInterval);

    float scanRadius() const;
    void setScanRadius(float scanRadius);

    CollisionFilter* filter();
    void setFilter(CollisionFilter* filter);

    const std::list<WorldObject*>& worldObjects();
    const std::list<WorldObject*>& foundWorldObjects();
    const std::list<WorldObject*>& lostWorldObjects();

    void update(float deltaSec, WorldObject* worldObject);
    void update(float deltaSec, const glm::vec3& position);

    virtual void onFoundWorldObject(WorldObject* worldObject);
    virtual void onLostWorldObject(WorldObject* worldObject);


protected:
    float m_scanInterval;
    float m_scanCountdown;

    float m_scanRadius;

    std::list<WorldObject*> m_worldObjects;

    std::list<WorldObject*> m_foundWorldObjects;
    std::list<WorldObject*> m_lostWorldObjects;

    std::unique_ptr<CollisionFilter> m_filter;


    void update(float deltaSec, WorldObject* worldObject, const glm::vec3& position);
    void scan(WorldObject* worldObject, const glm::vec3& position);
    void callHooks();
};

