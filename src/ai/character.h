#pragma once


class Ship;

class Character {
public:
    Character(Ship& ship);
    
    virtual void update(float deltaSec);

protected:
    Ship& m_ship;

};

