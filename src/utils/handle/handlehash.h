#pragma once

#include <functional>
#include "handle.h"

namespace std {
    template<typename A> struct hash<Handle<A>> {
        std::size_t operator()(const Handle<A> &h) const {
            return (std::size_t)(h.get());
        }
    };
}