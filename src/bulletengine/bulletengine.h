#pragma once


class Camera;

class BulletEngine {
public:
    BulletEngine();
    ~BulletEngine();

    void update(float deltaSec);
    void draw(const Camera& camera);
};
