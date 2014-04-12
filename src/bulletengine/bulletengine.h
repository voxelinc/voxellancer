#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>


class BulletEngineRenderer;
class Camera;
class InstancedBullet;
class InstancedBulletContainer;

/**
 * Responsible for much more performant handling of bullets instead of simulating them
 * like full WorldObjects
 * Holds the InstancedBullets of a World and their respective InstancedBulletContainers
 */
class BulletEngine {
public:
    BulletEngine();
    ~BulletEngine();

    BulletEngineRenderer& renderer();

    void add(InstancedBullet* bullet);

    /**
     * Retrieve or create the InstancedBulletContainer of the given name
     */
    InstancedBulletContainer* container(const std::string& name);

    /**
     * Create the InstancedBullet with the given name and connect it with its
     * respective InstancedBulletContainer
     */
    InstancedBullet* createBullet(const std::string& name);

    void update(float deltaSec);
    void draw(const Camera& camera);


protected:
    std::unordered_map<std::string, std::unique_ptr<InstancedBulletContainer>> m_containers;
    std::unordered_set<std::unique_ptr<InstancedBullet>> m_bullets;
    std::unique_ptr<BulletEngineRenderer> m_renderer;
};

