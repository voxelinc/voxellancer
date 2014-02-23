#pragma once

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

template<typename T>
class ThreadPool {
public:
    ThreadPool(std::function<void(T&)> function, int chunksize = 100);
    ~ThreadPool();

    void map(std::vector<T>& vector);
    void map(std::vector<T>& vector, int start, int end);

protected:
    void worker();
    int getTask();

    std::vector<T>* m_tasks;
    std::function<void(T&)> m_function;

    std::vector<std::thread> m_worker;
    std::condition_variable m_startSignal;
    std::condition_variable m_stopSignal;
    std::mutex m_lock;

    std::atomic_int m_index;
    int m_endIndex;
    int m_chunksize;
    bool m_exit;
    std::atomic_int m_runningWorkers;

};
template<typename T>
ThreadPool<T>::~ThreadPool() {
    m_exit = true;
    m_runningWorkers = m_worker.size();
    m_startSignal.notify_all();
    for (std::thread& thread : m_worker) {
        thread.join();
    }
}

template<typename T>
ThreadPool<T>::ThreadPool(std::function<void(T&)> function, int chunksize) :
    m_chunksize(chunksize),
    m_worker(2),
    m_function(function),
    m_tasks(nullptr),
    m_exit(false)
{
    m_runningWorkers = 0;
    for (int i = 0; i < m_worker.size(); i++) {
        m_worker[i] = std::thread(&ThreadPool<T>::worker, this);
    }
}

template<typename T>
void ThreadPool<T>::map(std::vector<T>& vector) {
    map(vector, 0, vector.size());
}

template<typename T>
void ThreadPool<T>::map(std::vector<T>& vector, int start, int end) {
    m_tasks = &vector;
    m_index = start;
    m_endIndex = end;

    m_runningWorkers = m_worker.size();
    m_startSignal.notify_all();

    std::mutex m;
    std::unique_lock<std::mutex> lk(m);
    m_stopSignal.wait(lk);
}

template<typename T>
void ThreadPool<T>::worker() {
    while (true) {
        std::unique_lock<std::mutex> lk(m_lock);
        m_startSignal.wait(lk, [&] { return m_runningWorkers == m_worker.size(); });
        lk.unlock(); // wait locks the mutex but the workers shouldn't wait on each other
        if (m_exit) {
            return;
        }

        int task;
        while ((task = getTask()) >= 0) {
            for (int i = task; i < task + m_chunksize; i++) {
                m_function((*m_tasks)[i]);
            }
        }

        if (--m_runningWorkers == 0) {
            m_stopSignal.notify_all();
        }
    }
}

template<typename T>
int ThreadPool<T>::getTask() {
    // get current value and increment
    int index = m_index.fetch_add(m_chunksize);

    if (index >= m_endIndex) {
        return -1;
    }
    return index;
}
