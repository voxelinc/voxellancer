#pragma once


class Ship;

class BasicTask {
public:
    BasicTask(Ship& ship);

    virtual void update(float deltaSec);
    virtual bool isInProgress();

protected:
    Ship& m_ship;
};

