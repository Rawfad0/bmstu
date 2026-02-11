#ifndef MTQUEUE_HPP
#define MTQUEUE_HPP

#include <queue>
#include <mutex>

#include "task.hpp"

template <typename T>
class Queue
{
public:
    Queue() {};

    void push(const T &task) {
        std::lock_guard<std::mutex> lock(_mtx);
        _queue.push(task);
    }

    T pop() {
        std::lock_guard<std::mutex> lock(_mtx);
        T task = _queue.front();
        _queue.pop();
        return task;
    }

    bool is_empty() const {
        std::lock_guard<std::mutex> lock(_mtx);
        return _queue.empty();
    };

private:
    std::queue<T> _queue;
    mutable std::mutex _mtx;
};

#endif // MTQUEUE_HPP
