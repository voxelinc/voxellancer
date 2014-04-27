#pragma once

#include <memory>

#include "input/inputhandler.h"


class Intro;
class Trigger;

class IntroInput : public InputHandler {
public:
    IntroInput(Intro& intro);
    ~IntroInput() override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;


protected:
    Intro& m_intro;
};

