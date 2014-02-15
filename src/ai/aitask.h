#pragma once


class Ship;

class AiTask {
public:
    AiTask(Ship& ship);

    virtual void update(float deltaSec);
    virtual bool isInProgress();

protected:
    Ship& m_ship;
};