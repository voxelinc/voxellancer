#pragma once


class Camera;
//class InstancedBullet;

class BulletEngine {
public:
    BulletEngine();
    ~BulletEngine();

//    InstancedBullet* createBullet(const std::string& name);

    void update(float deltaSec);
    void draw(const Camera& camera);
};

