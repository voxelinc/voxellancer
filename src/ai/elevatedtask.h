#pragma once


class Ship;

class ElevatedTask
{
public:
    ElevatedTask(Ship& ship);

    virtual void update(float deltaSec);

protected:
    Ship& m_ship;
};

