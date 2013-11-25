#pragma once


template <class T>
ClusterStore<T>::ClusterStore() :
m_items(),
m_loader() {

}

template <class T>
ClusterStore<T>::~ClusterStore() {

}

template <class T>
ClusterStore<T> *ClusterStore<T>::instance() {
    if (s_instance == nullptr) {
        s_instance = new ClusterStore();
    }
    return s_instance;
}

template <class T>
T *ClusterStore<T>::create(const std::string& name) {
    std::map<std::string, std::unique_ptr<T>>::iterator item = m_items.find(name);
    T *cluster = nullptr;
    if (item == m_items.end()){
        cluster = new T();
        m_loader.loadClusterFromFile((char*)name.c_str(), cluster);
        cluster->finishInitialization();
        m_items[name] = std::unique_ptr<T>(cluster);
    } else {
        cluster = item->second.get();
    }
    return new T(*cluster);
}
