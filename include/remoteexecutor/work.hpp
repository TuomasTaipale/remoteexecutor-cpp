#ifndef REMOTEEXECUTOR_WORK_HPP_
#define REMOTEEXECUTOR_WORK_HPP_

#include <functional>

namespace remoteexecutor
{
	using Work = std::function<void()>;
}

#endif
