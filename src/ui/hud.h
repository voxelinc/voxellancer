#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "property/property.h"
#include "camera.h"
#include "ui/hudelement.h"

class VoxelCluster;
class VoxelRenderer;

enum HUDFontSize {
    s3x5,
    s5x7
};

class HUD {
public:
    HUD(std::list<VoxelCluster*> ships);
    virtual ~HUD();

    void setCamera(Camera *camera);
    Camera *camera();

    void update(float delta_sec);
    void draw();

protected:
    void addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list);
    void addChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<VoxelCluster>> *map);

    void loadFont(const std::string& identifier, std::map<char, std::unique_ptr<VoxelCluster>> *map);
    void loadFonts();

    void stepAnim(glm::vec3 targetpos, glm::quat targetor);

    void drawString(std::string text, HUDOffsetOrigin origin, glm::vec3 offset, HUDFontSize size = HUDFontSize::s3x5, float scale = 1.f);
    void adjustPosition(VoxelCluster *cluster, HUDOffsetOrigin origin, glm::vec3 offset);
    void adjustPositions();

    

    Camera *m_gamecamera;
    WorldTransform m_hudcamera, m_lastgamecamera;
    Camera m_rendercamera;
    std::unique_ptr<VoxelRenderer> m_voxelRenderer;
    std::vector<std::unique_ptr<HUDElement>> m_elements;
    std::vector<std::unique_ptr<HUDElement>> m_numbers;
    std::map<char, std::unique_ptr<VoxelCluster>> m_font3x5;
    std::map<char, std::unique_ptr<VoxelCluster>> m_font5x7;
    std::unique_ptr<HUDElement> m_shiparrow;
    std::list<VoxelCluster*> m_ships;
    float m_delta_sec_remain;
    float m_framerate;
    float m_dx, m_dy;

    Property<float> m_distance, m_move_multiplier, m_inertia_move, m_inertia_rotate, m_inertia_rate,
        m_arrow_maxdistance, m_arrow_radius;
    Property<bool> m_show_framerate;

};