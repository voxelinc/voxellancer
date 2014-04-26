#pragma once

#include "aabb.h"


template<typename T>
TAABB<T> Line::containingAABB() const {
	glm::detail::tvec3<T> llf;
	glm::detail::tvec3<T> urb;

	if (m_a.x < m_b.x) {
		llf.x = m_a.x;
		urb.x = m_b.x;
	} else {
		llf.x = m_b.x;
		urb.x = m_a.x;
	}

	if (m_a.y < m_b.y) {
		llf.y = m_a.y;
		urb.y = m_b.y;
	} else {
		llf.y = m_b.y;
		urb.y = m_a.y;
	}

	if (m_a.z < m_b.z) {
		llf.z = m_a.z;
		urb.z = m_b.z;
	} else {
		llf.z = m_b.z;
		urb.z = m_a.z;
	}

	return TAABB<T>(llf, urb);
}

