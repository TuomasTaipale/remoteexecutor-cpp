#include "private/workqueue.hpp"

using namespace remoteexecutor;

void WorkQueue::push(Work&& work)
{
	std::lock_guard<std::mutex> guard { lock };

	queue.push(std::move(work));
}

std::optional<Work> WorkQueue::pop()
{
	std::lock_guard<std::mutex> guard { lock };

	if (queue.empty())
		return { };

	const auto work { std::make_optional<Work>(std::move(queue.front())) };

	queue.pop();

	return work;
}
