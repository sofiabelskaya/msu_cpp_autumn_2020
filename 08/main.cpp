#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

using namespace std;

class ThreadPool {

private:
    std::queue<std::function<void()> > queue_task;
    std::mutex mute;
    std::condition_variable condition;
    std::vector<std::thread> threads;
    std::atomic<bool> stop;

public:
    ThreadPool(size_t poolSize)
        : stop(false)
    {
        for (size_t i = 0; i < poolSize; i++) {
            threads.emplace_back([this] {
                this->thread_func();
            });
        }
    }
    ~ThreadPool()
    {
        stop = true;
        condition.notify_all();
        for (auto& i : threads) {
            i.join();
        }
    }
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        auto task = std::packaged_task<decltype(func(args...))()>(std::bind(func, args...));
        auto future = task.get_future();
        std::unique_lock<std::mutex> lock(mute);
        queue_task.push(std::move(task));
        condition.notify_one();
        return future;
    }
    void thread_func()
    {
        std::function<void()> task;
        while (true) {
            {
                std::unique_lock<std::mutex> lock(this->mute);
                this->condition.wait(lock, [this]() {
                    return (!this->queue_task.empty() || this->stop);
                });
                if (this->queue_task.size() == 0) {
                    break;
                }
                else {
                    task = this->queue_task.front();
                    this->queue_task.pop();
                }
            }
            task();
        }
    }
};
struct A {
};

void foo(const A&) {}

int main()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    task2.get();

    return 0;
}