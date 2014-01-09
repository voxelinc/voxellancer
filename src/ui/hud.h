#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "property/property.h"
#include "camera.h"
#include "ui/hudelement.h"

class VoxelRenderer;
class VoxelFont;
class Player;

class HUD {
public:
    HUD(Player *player);
    virtual ~HUD();

    void setCamera(Camera *camera);
    Camera *camera();

    void update(float deltaSec);
    void draw();

    void streamCallback(std::string line);

protected:
    void addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list);

    void stepAnim(glm::vec3 targetPosition, glm::quat targetOrientation);

    glm::vec3 calculatePosition(HUDOffsetOrigin origin, glm::vec3 offset);
    void adjustPositions();


    Player* m_player;
    Camera* m_gameCamera;
    WorldTransform m_hudCamera, m_lastGameCamera;
    Camera m_renderCamera;
    std::unique_ptr<VoxelRenderer> m_voxelRenderer;
    std::unique_ptr<VoxelFont> m_font;
    std::vector<std::unique_ptr<HUDElement>> m_elements;
    std::vector<std::unique_ptr<HUDElement>> m_numbers;

    std::unique_ptr<HUDElement> m_shipArrow;
    double m_delta_sec_remain;
    float m_frameRate;
    float m_dx, m_dy;

    std::vector<std::string> m_lastline;
    std::vector<double> m_lastlineTime;

    Property<float> prop_distance, prop_moveMultiplier, prop_inertiaMove, prop_inertiaRotate, prop_inertiaRate,
        prop_arrowMaxdistance, prop_arrowRadius;
    Property<bool> prop_showFramerate;
    Property<int> prop_lineBacklog;

};
