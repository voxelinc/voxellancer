#pragma once


class InputHandler {
public:
    virtual ~InputHandler();

    virtual void onKeyEvent(int key, int scancode, int action, int mods);
    virtual void onMouseButtonEvent(int button, int action, int mods);

    virtual void onResizeEvent(const unsigned int width, const unsigned int height);

    virtual void update(float deltaSec);
};

