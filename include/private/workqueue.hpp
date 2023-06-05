#ifndef REMOTEEXECUTOR_WORKQUEUE_HPP_
#define REMOTEEXECUTOR_WORKQUEUE_HPP_

#include <mutex>
#include <queue>
#include <remoteexecutor/work.hpp>

namespace remoteexecutor
{
	class WorkQueue
	{
	public:
		void push(Work&&);

		Work pop();

	private:
		std::mutex lock;
		std::queue<Work> queue;
	};
}

#endif
