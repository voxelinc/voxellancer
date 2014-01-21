#include <glm/glm.hpp>
#include "weapon.h"
#include "bullet.h"
#include "resource/clustercache.h"

class Gun : public Weapon {
public:
    Gun();
    virtual AimType aimType() override;
    virtual void shootAtPoint(Hardpoint* sourceHardpoint, glm::vec3 target) override;
    virtual void update(float deltaSec) override;
    virtual float bulletRange() override;


private:
    Property<float> m_bulletRange;
    Property<float> m_cooldownTime;
    Property<float> m_bulletSpeed;
};
