#ifndef QUEUE
#define QUEUE

#include <queue>
//#include <thread>
#include <mutex>
#include <condition_variable>

/** \class Queue
*
* \brief Provides a thread-safe wrapper for std::queue.
*
*/
template <typename T>
class Queue
{
	//variables
private:
	/** The internal std::queue */
	std::queue<T> m_internal_queue;
	/** Mutex and access variable to manage access to the internal queue */
	std::mutex m_access_mutex;
	std::condition_variable m_access_condition;

	//functions
public:
	T pop()
	{
		std::unique_lock<std::mutex> pop_lock(m_access_mutex);
		//while for multiple consumers
		while (m_internal_queue.empty())
		{
			m_access_condition.wait(pop_lock);
		}
		auto item = m_internal_queue.front();
		m_internal_queue.pop();
		return item;
	}

	void push(const T& item)
	{
		std::unique_lock<std::mutex> push_lock(m_access_mutex);
		m_internal_queue.push(item);
		push_lock.unlock();
		m_access_condition.notify_one();
	}

	bool empty()
	{
		return m_internal_queue.empty();
	}

	size_t size()
	{
		return m_internal_queue.size();
	}
};

#endif //QUEUE