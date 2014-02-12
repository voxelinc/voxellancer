#include <glm/glm.hpp>

#include "weapon.h"
#include "property/property.h"

class Gun : public Weapon {
public:
    Gun();

    virtual AimType aimType() override;
    virtual float bulletSpeed() const override;
    virtual float range() override;

    virtual void shootAtPoint(Hardpoint* sourceHardpoint, glm::vec3 target) override;

    virtual void update(float deltaSec) override;


private:
    Property<float> m_range;
    Property<float> m_cooldownTime;
    Property<float> m_bulletSpeed;
};
