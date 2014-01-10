#include "camera.h"

#include <glm/gtx/transform.hpp>


Camera::Camera(int viewportWidth, int viewportHeight):
	m_fovy(60.f),
	m_aspect(1.f),
	m_zNear(1),
	m_zFar(9999)
{
    setViewport(glm::ivec2(viewportWidth, viewportHeight));
}

Camera::~Camera(){

}

void Camera::viewDirty(){
	m_view = glm::mat4_cast(glm::inverse(m_orientation)) * glm::translate(-m_position);
	m_viewProjection = m_projection * m_view;
}

void Camera::projectionDirty(){
	m_projection = glm::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
	m_viewProjection = m_projection * m_view;
}

void Camera::move(glm::vec3 dist){
	WorldTransform::move(dist);
	viewDirty();
}

void Camera::setPosition(glm::vec3 pos){
	WorldTransform::setPosition(pos);
	viewDirty();
}

void Camera::rotateX(float rot){
	WorldTransform::rotate(glm::angleAxis(rot, glm::vec3(1,0,0)));
	viewDirty();
}

void Camera::rotateY(float rot){
    WorldTransform::rotate(glm::angleAxis(rot, glm::vec3(0, 1, 0)));
	viewDirty();
}

void Camera::rotateZ(float rot){
    WorldTransform::rotate(glm::angleAxis(rot, glm::vec3(0, 0, -1)));
	viewDirty();
}

void Camera::setOrientation(glm::quat quat){
	WorldTransform::setOrientation(quat);
	viewDirty();
}

const glm::mat4 Camera::view(){
	return m_view;
}

const glm::mat4 Camera::viewInverted(){
	return glm::inverse(m_view);
}

const glm::quat Camera::orientation(){
	return WorldTransform::orientation();
}

const glm::vec3 Camera::position() {
    return m_position;
}

float Camera::zNear() const {
	return m_zNear;
}

void Camera::setZNear(const float zNear) {
	if (zNear == m_zNear) {
		return;
    }

	m_zNear = zNear;
	assert(m_zNear > 0.0);

	projectionDirty();
}

float Camera::zFar() const {
	return m_zFar;
}

void Camera::setZFar(const float zFar) {
	if (zFar == m_zFar) {
		return;
    }

	m_zFar = zFar;
	assert(m_zFar > m_zNear);
    projectionDirty();
}

float Camera::fovy() const {
	return m_fovy;
}

void Camera::setFovy(const float fovy) {
	if (fovy == m_fovy) {
		return;
    }

	m_fovy = fovy;
	assert(m_fovy > 0.0);
    projectionDirty();
}

const glm::ivec2 Camera::viewport() const {
	return m_viewport;
}

void Camera::setViewport(const glm::ivec2& viewport) {
	if (viewport == m_viewport) {
		return;
    }

	m_aspect = viewport.x / glm::max(static_cast<float>(viewport.y), 1.f);
	m_viewport = viewport;
    projectionDirty();
}

float Camera::aspectRatio() const {
	return m_aspect;
}

const glm::mat4 Camera::projection() {
	return m_projection;
}

const glm::mat4 Camera::viewProjection() {
	return m_viewProjection;
}
