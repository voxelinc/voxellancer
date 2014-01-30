#pragma once


class Ship;

class AiTask {
public:
    AiTask(Ship& ship);

    virtual void update(float deltaSec);

protected:
    Ship& m_ship;
};

