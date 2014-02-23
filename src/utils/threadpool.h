#pragma once

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

template<typename T>
class ThreadPool {
public:
    ThreadPool(std::function<void(T&)> function);
    ~ThreadPool();

    void map(std::vector<T>& vector);

protected:
    void worker();
    int getTask();

    std::vector<T>* m_tasks;
    std::function<void(T&)> m_function;

    std::vector<std::thread> m_worker;
    std::condition_variable m_startsignal;
    std::condition_variable m_stopsignal;
    std::mutex m_lock;

    int m_index;
    int m_chunksize;
    bool m_exit;
    std::atomic_int m_running;

};

template<typename T>
ThreadPool<T>::~ThreadPool() {
    m_running = m_worker.size();
    m_startsignal.notify_all();
    for (std::thread& thread: m_worker) {
        thread.join();
    }
}

template<typename T>
ThreadPool<T>::ThreadPool(std::function<void(T&)> function) :
    m_chunksize(100),
    m_worker(2),
    m_function(function),
    m_tasks(nullptr),
    m_exit(false)
{
    m_running = 0;
    for (int i = 0; i < m_worker.size(); i++) {
        m_worker[i] = std::thread(&ThreadPool<T>::worker, this);
    }
}

template<typename T>
void ThreadPool<T>::map(std::vector<T>& vector) {
    m_tasks = &vector;
    m_index = 0;
    
    m_running = m_worker.size();
    m_startsignal.notify_all();

    std::unique_lock<std::mutex> lk(m_lock);
    m_stopsignal.wait(lk, [&] { return m_running == 0; });
}

template<typename T>
void ThreadPool<T>::worker() {
    std::unique_lock<std::mutex> lk(m_lock);

    while (true) {
        m_startsignal.wait(lk, [&] { return m_running > 0; });
        if (m_exit) {
            return;
        }
        int task;
        while (task = getTask() >= 0) {
            for (int i = task; i < task + m_chunksize; i++) {
                m_function((*m_tasks)[i]);
            }
        }
        m_running--;
        m_stopsignal.notify_all();
    }
}

template<typename T>
int ThreadPool<T>::getTask() {
    m_lock.lock();
    int index = m_index;
    m_index += m_chunksize;
    m_lock.unlock();

    if (index >= m_tasks->size()) {
        return -1;
    }
    return index;
}

