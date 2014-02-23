#pragma once

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

template<typename T>


class ThreadPool {
public:
    ThreadPool(int threadcount = 4, int chunksize = 100);
    ~ThreadPool();

    void map(std::function<void(T&)> function, std::vector<T>& vector);
    void map(std::function<void(T&)> function, std::vector<T>& vector, int start, int end);

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

#include "threadpool.inl"