#pragma once

#include "display/scene.h"


class Intro;

class IntroScene : public Scene {
public:
    IntroScene(Intro& intro);

    void update(float deltaSec) override;


protected:
    Intro& m_intro;

    void drawImpl(const Camera& camera) const override;
};

