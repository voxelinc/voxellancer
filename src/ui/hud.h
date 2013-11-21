#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "property/property.h"
#include "camera.h"
#include "ui/hudelement.h"

class VoxelCluster;
class VoxelRenderer;

class HUD {
public:
    HUD(std::list<VoxelCluster*> ships);
    virtual ~HUD();

    void setCamera(Camera *camera);
    Camera *camera();

    void update(float delta_sec);
    void draw();

protected:
    void adjustPositions();
    void addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list);
    void stepAnim(glm::vec3 targetpos, glm::quat targetor);

    Camera *m_gamecamera;
    WorldTransform m_hudcamera, m_lastgamecamera;
    Camera m_rendercamera;
    std::unique_ptr<VoxelRenderer> m_voxelRenderer;
    std::vector<std::unique_ptr<HUDElement>> m_elements;
    std::vector<std::unique_ptr<HUDElement>> m_numbers;
    std::unique_ptr<HUDElement> m_shiparrow;
    std::list<VoxelCluster*> m_ships;
    float m_delta_sec_remain;
    float m_framerate;

    Property<float> m_distance, m_move_multiplier, m_inertia_move, m_inertia_rotate, m_inertia_rate, m_arrow_maxdistance, m_arrow_radius;
    Property<bool> m_show_framerate;
};