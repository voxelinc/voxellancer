#pragma once

#include <string>
#include <unordered_map>


class Camera;
class InstancedBullet;
class InstancedBulletPrototype;

class BulletEngineRenderer {
public:
    BulletEngineRenderer();

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    void draw(const Camera& camera);

protected:
    std::unordered_map<std::string, InstancedBulletPrototype*> m_prototypes;
};

