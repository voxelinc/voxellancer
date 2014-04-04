#pragma once

#include <memory>


class HandleOwner;

class HandleImpl {
public:
    explicit HandleImpl(HandleOwner* owner);

    HandleOwner* owner();

    bool valid() const;
    void invalidate();


protected:
    HandleOwner* m_owner;
};

