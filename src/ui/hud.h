#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "property/property.h"
#include "camera.h"
#include "ui/hudelement.h"

class VoxelRenderer;
class Letter;
class VoxelFont;

class HUD {
public:
    HUD();
    virtual ~HUD();

    void setCamera(Camera *camera);
    Camera *camera();

    void update(float delta_sec);
    void draw();

protected:
    void addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list);

    void addChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<Letter>> *map);

    void loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<Letter>> *map);
    void loadFonts();


    void stepAnim(glm::vec3 targetPosition, glm::quat targetOrientation);

    glm::vec3 calculatePosition(HUDOffsetOrigin origin, glm::vec3 offset);
    void adjustPositions();



    Camera *m_gameCamera;
    WorldTransform m_hudCamera, m_lastGameCamera;
    Camera m_renderCamera;
    std::unique_ptr<VoxelRenderer> m_voxelRenderer;
    std::unique_ptr<VoxelFont> m_font;
    std::vector<std::unique_ptr<HUDElement>> m_elements;
    std::vector<std::unique_ptr<HUDElement>> m_numbers;

    std::map<char, std::unique_ptr<Letter>> m_font3x5;
    std::map<char, std::unique_ptr<Letter>> m_font5x7;

    std::unique_ptr<HUDElement> m_shipArrow;
    double m_delta_sec_remain;
    float m_frameRate;
    float m_dx, m_dy;

    Property<float> prop_distance, prop_moveMultiplier, prop_inertiaMove, prop_inertiaRotate, prop_inertiaRate,
        prop_arrowMaxdistance, prop_arrowRadius;
    Property<bool> prop_showFramerate;

};
