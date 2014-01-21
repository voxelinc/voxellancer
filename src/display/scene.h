#pragma once

class Camera;

class Scene {
public:
    virtual void draw(Camera* camera) = 0;
};

