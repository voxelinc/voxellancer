#include "util/observer.h"

class WorldObjectComponents;

class ComponentsInfo : public Observer {
public:
    ComponentsInfo(WorldObjectComponents* worldObject);

    float maxBulletRange() const;
    float maxForwardSpeed() const;
    float maxRocketRange() const;

    void updateInfo();

    void updateObserver();

private:
    WorldObjectComponents* m_components;

    void calculateBulletRange();
    void calculateForwardSpeed();
    void calculateRocketRange();

    float m_maxBulletRange;
    float m_maxForwardSpeed;
    float m_maxRocketRange;
};