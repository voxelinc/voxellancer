

class WorldObject;

class ComponentsInfo {
public:
    ComponentsInfo(WorldObject* worldObject);

    float maxBulletRange();
    float maxRocketRange();
    float maxForwardSpeed();

    void updateInfo();

private:
    WorldObject* m_worldObject;

    float m_maxBulletRange;
    float m_maxRocketRange;
    float m_maxForwardSpeed;
};