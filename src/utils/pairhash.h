#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <utility>

namespace std {
    template<typename A, typename B>
    struct hash<pair<A, B>> {
        size_t operator()(const pair<A, B>& arg) const {
            std::hash<A> hashA;
            std::hash<B> hashB;
            return hashA(arg.first) ^ (hashB(arg.second) * 31);
        }
    };
}
