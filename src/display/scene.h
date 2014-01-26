#pragma once

class Camera;

class Scene {
public:
    virtual void draw(Camera* camera) = 0;
    virtual void update(float deltaSec) = 0;

    // is called by the viewer
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    
};

