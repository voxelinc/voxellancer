

class WorldObject;

class ComponentsInfo {
public:
    ComponentsInfo(WorldObject* worldObject);

    const float maxBulletRange() const;
    const float maxForwardSpeed() const;

    void updateInfo();

private:
    WorldObject* m_worldObject;

    float m_maxBulletRange;
    float m_maxForwardSpeed;
};