#ifndef REMOTEEXECUTOR_WORK_HPP_
#define REMOTEEXECUTOR_WORK_HPP_

#include <tuple>
#include <memory>

namespace remoteexecutor
{
	class Work
	{
	public:
		Work()
		{
		}

		template <class Callable, class ...Args>
		explicit Work(Callable callable, Args ...args):
			work { std::make_unique<ActualWorkImpl<Callable, Args...>>(
								std::forward<Callable>(callable),
								std::forward<Args>(args)...) }
		{
		}

		Work(Work&& other)
		{
			if (this != &other)
				work = std::move(other.work);
		}

		Work& operator=(Work&& other)
		{
			if (this != &other)
				work = std::move(other.work);

			return *this;
		}

		void operator()()
		{
			work->call();
		}

		operator bool() const
		{
			return static_cast<bool>(work);
		}

	private:
		struct ActualWork
		{
			virtual ~ActualWork() = default;
			virtual void call() = 0;
		};

		template <class Callable, class ...Args>
		struct ActualWorkImpl: public ActualWork
		{
			Callable callable;
			std::tuple<Args...> args;

			ActualWorkImpl(Callable callable, Args ...args):
				callable{ std::forward<Callable>(callable) },
				args { std::make_tuple(std::forward<Args>(args)...) }
			{
			}

			template <std::size_t ...seq>
			void callImpl(std::index_sequence<seq...>)
			{
				callable(std::get<seq>(args)...);
			}

			void call() override
			{
				callImpl(std::index_sequence_for<Args...> { });
			}
		};

		std::unique_ptr<ActualWork> work;
	};
}

#endif
