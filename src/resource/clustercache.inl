#pragma once

template <class T>
T* ClusterCache::clone(T* other){
    return new T(*other);
}