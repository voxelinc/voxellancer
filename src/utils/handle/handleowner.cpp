#include "handleowner.h"


HandleOwner::HandleOwner():
    m_impl(new HandleImpl(this))
{
}

HandleOwner::~HandleOwner() {
    m_impl->invalidate();
}

void HandleOwner::invalidate() {
    m_impl->invalidate();
}

