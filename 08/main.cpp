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
    std::deque<std::packaged_task<void()> > queue_task;
    std::mutex mute;
    std::condition_variable condition;
    std::vector<std::thread> threads;
    std::atomic<bool> stop;

public:
    ThreadPool(size_t poolSize)
        : stop(false)
    {
        //cout<<"ThreadPool(size_t poolSize)"<<endl;
        for (size_t i = 0; i < poolSize; i++) {
            threads.emplace_back([this] {
                this->thread_func();
            });
        }
    }
    inline ~ThreadPool()
    {

        {
            //cout<<"~ThreadPool()"<<endl;
            stop = true;
        }
        condition.notify_all();
        for (auto& i : threads) {
            i.join();
        }
    }
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        //cout<<"exec()"<<endl;
        std::packaged_task<decltype(func(args...))()> task(std::bind(func, args...));
        auto future = task.get_future();
        {
            std::unique_lock<std::mutex> lock(mute);
            queue_task.emplace_back(std::move(task));
        }
        condition.notify_one();
        return future;
    }
    void thread_func()
    {
        //cout<<"thread_func()"<<endl;
        // std::function<void()> task;
        while (true) {
            std::packaged_task<void()> task;
            {
                std::unique_lock<std::mutex> lock(this->mute);
                condition.wait(lock, [&] { return !this->queue_task.empty() || stop; });
                if (!queue_task.empty()) {
                    task = std::move(this->queue_task.front());
                    this->queue_task.pop_front();
                }
                else {
                    break;
                }
            }
            if (!task.valid())
                break;
            task();
        }
    }
};

struct A {
};

void foo(const A&) { cout << "foo" << endl; }
void a()
{
    cout << "Running a" << endl;
}

int main()
{
    //lecture example
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    task2.get();

    //tutorial example test
    ThreadPool pool_(4);
    std::vector<std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool_.exec([i] {
                std::cout << "i " << i << std::endl;
                return i * i;
            }));
    }
    for (auto& result : results) {
        std::cout << result.get() << ' ';
        std::cout << std::endl;
    }
    return 0;
}
