#include <remoteexecutor/executor.hpp>
#include "private/workqueue.hpp"

using namespace remoteexecutor;

struct Executor::ExecutorData
{
	WorkQueue in;
	WorkQueue out;
};

Executor::Executor(uint32_t count):
	count { count },
	next { 0U },
	isRunning { false },
	executorData { count }
{
	isRunning = true;

	for (auto& i: executorData)
		executors.push_back(std::thread { std::bind(&Executor::remoteExecute, this,
							    std::ref(i)) });
}

Executor::~Executor()
{
	isRunning = false;

	for (auto& i: executors)
		i.join();
}

uint32_t Executor::getCount() const
{
	return count;
}

void Executor::setReadyHandler(ReadyHandler&& handler)
{
	this->handler = handler;
}

void Executor::unsetReadyHandler()
{
	handler = { };
}

void Executor::execute(Work&& work)
{
	executorData.at(next++ % count).in.push(std::move(work));
}

void Executor::execute(Work&& work, uint32_t executorId)
{
	executorData.at(executorId).in.push(std::move(work));
}

void Executor::handleReady()
{
	for (auto& i: executorData) {
		auto work { i.out.pop() };

		if (work && handler)
			handler(std::move(work));
	}
}

void Executor::remoteExecute(ExecutorData& data) noexcept
{
	while (isRunning.load()) {
		auto work { data.in.pop() };

		if (work) {
			(work)();
			data.out.push(std::move(work));
		}
	}
}
