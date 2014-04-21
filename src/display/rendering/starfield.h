#pragma once

#include <deque>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/ref_ptr.h>

#include "property/property.h"
#include "display/rendering/renderpass.h"
#include "etc/contextdependant.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
};



/*
   Renders a starfield around the camera.
   Old camera positions/orientations are stored in order to stretch the
   Stars on movement. As stereorendering renders twice per frame
   with slightly different cameras, the Starfield needs to know which
   side is drawn currently.
   http://chrdw.de/uploads/Eyeside.pdf
*/
class Starfield : public RenderPass, public ContextDependant {
public:
    Starfield();

    virtual void update(float deltaSec, const glm::vec3& cameraPosition);
    virtual void apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) override;


protected:
    struct StarData {
        glm::vec3 pos;
        float brightness;
        float size;
    };
    struct CameraLocation {
        float time;
        glm::vec3 position;
        glm::quat orientation;
    };

    std::deque<CameraLocation> m_locations[2];
    float m_time;
    Property<float> m_starfieldAge;
    Property<float> m_starSize;
    Property<int> m_starCount;
    Property<float> m_fieldRadius;
    float m_oldFieldRadius;

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_gpuBuffer;
    std::vector<StarData> m_cpuBuffer;

    void createAndSetupShaders();
    void createAndSetupGeometry();

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;

    void createBinding(int index, std::string name, int offset, int size);

    void addLocation(const Camera& camera, int side);
    glm::mat4 getMatrixFromPast(const Camera& camera, int side);
    void cleanUp(int side);
};

