#include "rendermetadata.h"


RenderMetaData::RenderMetaData(const Camera& camera, EyeSide eyeside):
    m_camera(camera),
    m_eyeside(eyeside)
{
}


const Camera& RenderMetaData::camera() const {
    return m_camera;
}

EyeSide RenderMetaData::eyeside() const {
    return m_eyeside;
}
