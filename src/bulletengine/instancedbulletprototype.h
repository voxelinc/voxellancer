#pragma once

#include <string>


class Camera;
class InstancedBullet;

class InstancedBulletPrototype {
public:
    InstancedBulletPrototype(const std::string& name);

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    void draw(const Camera& camera);


protected:
    bool m_initialized;


    void initialize();
};

