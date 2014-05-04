#pragma once

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

/**
 * The threadpool allows to distribute work to multiple threads.
 * The works needs a function f(x) and a vector<x>. f gets executed
 * for every value in vector.
 * The threadpool uses conditionvariables and atomic_ints to communicate.
 */
template<typename T>
class ThreadPool {
public:
    ThreadPool(int threadcount = 4, int chunksize = 100);
    ~ThreadPool();

    // calls function(element) for every element in data
    void map(std::function<void(T&)> function, std::vector<T>& data);
    // calls a function(element) for every element in data[start:end] (inclusive start, exclusive end)
    void map(std::function<void(T&)> function, std::vector<T>& data, int start, int end);

protected:
    void startWorkers();
    void worker();
    int getTask();

    std::vector<T>* m_tasks;
    std::function<void(T&)> m_function;

    std::vector<std::thread> m_workers;
    std::condition_variable m_startSignal;
    std::condition_variable m_stopSignal;
    std::mutex m_mutex;

    std::atomic_int m_currentIndex;
    int m_endIndex;
    int m_chunksize;

    bool m_exit;
    std::atomic_int m_startWorkers;
    std::atomic_int m_stoppedWorkers;

};

#include "threadpool.inl"
