#include "threadpool.h"


template<typename T>
ThreadPool<T>::ThreadPool(int threadcount, int chunksize) :
    m_chunksize(chunksize),
    m_workers(threadcount),
    m_tasks(nullptr),
    m_exit(false),
    m_startWorkers(),
    m_stoppedWorkers(),
    m_mutex(),
    m_index()
{
    m_startWorkers = 0;
    m_stoppedWorkers = m_workers.size();
    for (int i = 0; i < m_workers.size(); i++) {
        m_workers[i] = std::thread(&ThreadPool<T>::worker, this);
    }
}

template<typename T>
ThreadPool<T>::~ThreadPool() {
    m_exit = true;
    startWorkers();
    for (std::thread& thread : m_workers) {
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
    m_currentIndex = start;
    m_endIndex = end;

    startWorkers();

    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    m_stopSignal.wait(lock); // wait for workers to finish
}

template<typename T>
void ThreadPool<T>::startWorkers() {
    assert(m_stoppedWorkers == m_workers.size());
    assert(m_startWorkers == 0);
    m_stoppedWorkers = 0;
    m_startWorkers = m_workers.size();
    m_startSignal.notify_all();
}

template<typename T>
void ThreadPool<T>::worker() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_startSignal.wait(lock, [&] { return m_startWorkers > 0; });
        if (m_exit) {
            return;
        }
        m_startWorkers--;
        lock.unlock();
        
        //std::cout << "work" << std::this_thread::get_id() << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(1));

        int task;
        while ((task = getTask()) >= 0) {
            int end = std::min(task + m_chunksize, m_endIndex);
            for (int i = task; i < end; i++) {
                m_function((*m_tasks)[i % m_tasks->size()]);
            }
        }

        lock.lock();
        if (++m_stoppedWorkers == m_workers.size()) {
            m_stopSignal.notify_one();
        }
    }
}

template<typename T>
int ThreadPool<T>::getTask() {
    // get current value and increment by chunksize
    int index = m_currentIndex.fetch_add(m_chunksize);

    if (index >= m_endIndex) {
        return -1;
    }
    return index;
}
