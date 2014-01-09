#pragma once


class Ship;

class BasicTask {
public:
    BasicTask(Ship& ship);

    virtual void update(float deltaSec);

protected:
    Ship& m_ship;
};

