#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>


class BulletEngineRenderer;
class Camera;
class InstancedBullet;
class InstancedBulletContainer;

class BulletEngine {
public:
    BulletEngine();
    ~BulletEngine();

    BulletEngineRenderer& renderer();

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    InstancedBulletContainer* container(const std::string& name);

    InstancedBullet* createBullet(const std::string& name);

    void update(float deltaSec);
    void draw(const Camera& camera);


protected:
    std::unordered_map<std::string, std::unique_ptr<InstancedBulletContainer>> m_containers;
    std::unordered_set<InstancedBullet*> m_bullets;
    std::unique_ptr<BulletEngineRenderer> m_renderer;
};

