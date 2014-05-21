#pragma once


class GamePlay;
class Universe;

class BaseScenario {
public:
    BaseScenario(Universe& universe);

    void load();


protected:
    Universe& m_universe;

    virtual void createUniverse();
    virtual void populateUniverse();
    virtual void startScripts();
};

