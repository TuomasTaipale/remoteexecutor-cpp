#ifndef REMOTEEXECUTOR_EXECUTOR_HPP_
#define REMOTEEXECUTOR_EXECUTOR_HPP_

#include <atomic>
#include <cstdint>
#include <functional>
#include <thread>
#include <vector>
#include <remoteexecutor/work.hpp>

namespace remoteexecutor
{
	class Executor
	{
	public:
		explicit Executor(uint32_t count);

		~Executor();

		uint32_t getCount() const;

		using ReadyHandler = std::function<void(Work&&)>;

		void setReadyHandler(ReadyHandler&& handler);

		void unsetReadyHandler();

		void execute(Work&& work);

		void execute(Work&& work, uint32_t executorId);

		void handleReady();

		Executor(const Executor&) = delete;
		Executor& operator=(const Executor&) = delete;

	private:
		struct ExecutorData;

		const uint32_t count;
		uint32_t next;
		std::atomic_bool isRunning;
		ReadyHandler handler;
		std::vector<ExecutorData> executorData;
		std::vector<std::thread> executors;

		void remoteExecute(ExecutorData& data) noexcept;
	};
}

#endif
