#ifndef SCHED_PROCESS_H
# define SCHED_PROCESS_H
# include <mutex>
# include <condition_variable>
namespace sched
{
	template<typename TConfig>
	class process
	{
		typedef typename TConfig::cfg_clock clock;

		static std::mutex suspend_lock;

		static bool       started;

		struct process_control
		{
			process_control() {}


		};

	public:

		static void start()
		{
			started = true;

			while(started)
			{
				TConfig::task(process_control())
				// Do the work
			
			}
		}

		static void stop()
		{}

		static void notify()
		{}
		
	};

	template<typename c>
	std::mutex process<c>::suspend_lock;

	template<typename c>
	std::condition_variable process::suspend_cv;
}
#endif
