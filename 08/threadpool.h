#include <condition_variable>
#include <functional>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <queue>

#include <iostream>
	
class ThreadPool {
private:

	std::mutex _mutex;
	std::condition_variable _queue_cond;

	std::queue<std::function<void()>> _queue;
	std::vector<std::thread> _thread_pool;
	bool _stop = false;

public:
	explicit ThreadPool(size_t poolSize) {
		for (size_t i = 0; i < poolSize; ++i) {
			_thread_pool.emplace_back([this]() {
					while (true) {
						std::function<void()> task;
						{
							std::unique_lock<std::mutex> lock(this->_mutex);
							while (this->_queue.empty() && !this->_stop)
								this->_queue_cond.wait(lock);

							if (this->_stop)
								return;

							task = std::move(this->_queue.front());
							this->_queue.pop();
						}

						task();
					}
				}
			);
		}
	}

	~ThreadPool() {
		{
			std::unique_lock<std::mutex> lock(_mutex);
			_stop = true;
		}

		_queue_cond.notify_all();
		for (size_t i = 0; i < _thread_pool.size(); ++i)
			_thread_pool[i].join();
	}

	template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {

    	std::future<decltype(func(args...))> future;
    	{
    		std::unique_lock<std::mutex> lock(_mutex);

    		auto bindFunc = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
	    	auto task = new std::packaged_task<decltype(func(args...))()>(bindFunc);

	    	future = task->get_future();
	    	_queue.emplace([task]() {
	    		(*task)();
	    		delete task;
	    	});
    	}

    	_queue_cond.notify_one();
    	return future;
    }
};