#include "threadpool.h"


template<typename T>
ThreadPool<T>::ThreadPool(int threadcount, int chunksize) :
    m_chunksize(chunksize),
    m_worker(threadcount),
    m_tasks(nullptr),
    m_exit(false),
    m_running(),
    m_runningWorkers(),
    m_mutex(),
    m_index()
{
    m_running = false;
    m_runningWorkers = 0;
    for (int i = 0; i < m_worker.size(); i++) {
        m_worker[i] = std::thread(&ThreadPool<T>::worker, this);
    }
}

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
void ThreadPool<T>::map(std::function<void(T&)> function, std::vector<T>& data) {
    map(function, data, 0, data.size());
}

template<typename T>
void ThreadPool<T>::map(std::function<void(T&)> function, std::vector<T>& data, int start, int end) {
    if (end - start == 0) {
        return;
    }
    m_function = function;
    m_tasks = &data;
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
        m_startSignal.wait(lock, [&] { return m_running == true; });
        if (m_exit) {
            return;
        }
        m_runningWorkers++;
        lock.unlock();
        
        // std::cout << "work" << std::this_thread::get_id() << std::endl;

        int task;
        while ((task = getTask()) >= 0) {
            int end = std::min(task + m_chunksize, m_endIndex);
            for (int i = task; i < end; i++) {
                m_function((*m_tasks)[i % m_tasks->size()]);
            }
        }

        lock.lock();
        m_running = false;
        if (--m_runningWorkers == 0) {
            m_stopSignal.notify_one();
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
