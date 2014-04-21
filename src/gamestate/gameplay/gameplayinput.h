#pragma once

class GamePlayInput {
public:

    virtual void resizeEvent(const unsigned int width, const unsigned int height);
    virtual void keyCallback(int key, int scancode, int action, int mods);
    virtual void mouseButtonCallback(int button, int action, int mods);
    virtual void update(float deltaSec);

};
