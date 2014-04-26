#include "handleimpl.h"

#include <cassert>


HandleImpl::HandleImpl(HandleOwner* owner):
    m_owner(owner)
{
}

HandleOwner* HandleImpl::owner() {
    return m_owner;
}

bool HandleImpl::valid() const {
    return m_owner != nullptr ;
}

void HandleImpl::invalidate() {
    m_owner = nullptr;
}

