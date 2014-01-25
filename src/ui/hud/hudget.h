#pragma once


class HUD;

class Hudget {
public:
    Hudget(HUD* hud);

    HUD* hud();

    virtual void update(float deltaSec) = 0;
    virtual void draw() = 0;


protected:
    HUD* m_hud;
};

