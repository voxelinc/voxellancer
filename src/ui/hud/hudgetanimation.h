#pragma once


class Hudget;

/**
 *  Base class for Animations of Hudgets
 */
class HudgetAnimation {
public:
    HudgetAnimation(Hudget& hudget);

    Hudget& hudget();

    bool active() const;
    void setActive(bool active);

    virtual void update(float deltaSec);


protected:
     Hudget& m_hudget;
     bool m_active;
};

