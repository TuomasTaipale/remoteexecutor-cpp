#include "private/workqueue.hpp"

using namespace remoteexecutor;

void WorkQueue::push(Work&& work)
{
	std::lock_guard<std::mutex> guard { lock };

	queue.push(std::move(work));
}

Work WorkQueue::pop()
{
	std::lock_guard<std::mutex> guard { lock };

	if (queue.empty())
		return { };

	auto work { std::move(queue.front()) };

	queue.pop();

	return work;
}
