#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <remoteexecutor/executor.hpp>
#include <remoteexecutor/work.hpp>

namespace
{
	struct Task1
	{
		void operator()(uint32_t computation1, uint32_t computation2)
		{
			computation1 += 1234;
			computation2 += 1337;
			std::cout << "work done, comp1: " << computation1 << " comp2: "
				  << computation2 << std::endl;
		}
	};

	void task2(uint32_t init)
	{
		uint32_t computation1 = init, computation2 = init;

		std::this_thread::sleep_for(std::chrono::milliseconds { 200 });
		computation1 += 1234;
		computation2 += 1337;
		std::cout << "work done, comp1: " << computation1 << " comp2: " << computation2
			  << std::endl;
	}
}

int main()
{
	remoteexecutor::Executor e { 10U };
	uint32_t taskCounter { 0U };
	bool isRunning { true };
	Task1 task;
	const uint32_t init { 3000U };

	e.setReadyHandler([&taskCounter, &isRunning](remoteexecutor::Work&&)
		{
			if (++taskCounter == 3U)
				isRunning = false;
		});
	e.execute(remoteexecutor::Work { std::move(task), 1000U, 1000U });
	e.execute(remoteexecutor::Work { task2, 2000U });
	e.execute(remoteexecutor::Work { [init](){
		uint32_t computation1 = init, computation2 = init;

		std::this_thread::sleep_for(std::chrono::milliseconds { 400 });
		computation1 += 1234;
		computation2 += 1337;
		std::cout << "work done, comp1: " << computation1 << " comp2: " << computation2
			  << std::endl;
	} });

	while (isRunning)
		e.handleReady();

	return EXIT_SUCCESS;
}
