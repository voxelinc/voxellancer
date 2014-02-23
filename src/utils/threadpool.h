#pragma once

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include <iostream>

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
    std::mutex m_mutex;

    int m_endIndex;
    int m_chunksize;
    std::atomic_int m_index;

    bool m_exit;
    bool m_running;
    std::atomic_int m_runningWorkers;

};
template<typename T>
ThreadPool<T>::~ThreadPool() {
    m_exit = true;
    m_running = true;
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
    m_running(false),
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

    m_running = true;
    m_startSignal.notify_all();

    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    m_stopSignal.wait(lock);
}

template<typename T>
void ThreadPool<T>::worker() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_startSignal.wait(lock, [&] { return m_running; });
        if (m_exit) {
            std::cout << "exit " << std::this_thread::get_id() << std::endl;
            return;
        }
        m_runningWorkers++;
        lock.unlock(); 
        
        std::cout << "work " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int task;
        while ((task = getTask()) >= 0) {
            for (int i = task; i < task + m_chunksize; i++) {
                m_function((*m_tasks)[i]);
            }
        }

        lock.lock();
        std::cout << "finish " << std::this_thread::get_id() << std::endl;
        m_running = false;
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