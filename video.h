#ifndef WIC_VIDEO_H
# define WIC_VIDEO_H
# include <alsa_host.h>
# include <exception>
# include <functional>
# include <video/stream_reader.h>
namespace wic
{
	template<typename TConfig>
	class video
	{
		static ::video::stream_reader *stream;

		static std::thread *process;

		static volatile bool running;

		static sched::event<::video::frame> on_frame;

		static void frame_handler(::video::frame f)
		{ on_frame(f); }

		static void start()
		{
			while(!stream && running)
			{
				try
				{
					stream = new ::video::stream_reader(TConfig::cfg_source);
				}
				catch(int ex)
				{
					journal(journal::critical,"wic.video")  << TConfig::name << ": could not initialize source; retrying in 3 seconds" << journal::end;
					std::this_thread::sleep_for(std::chrono::seconds(3));
					continue;
					
				}
				stream->on_frame += frame_handler;

				while(running)
				{
					try
					{ stream->process_frame(); }
					catch(int ex)
					{
						journal(journal::critical,"wic.video")  << TConfig::name << ": source disconnected; trying to reinitialize" << journal::end;
						delete stream;
						stream = 0;
						break;
					}
				}
			}

		}


	public:
		static void init()
		{
			running = true;
			process = new std::thread(start);
#ifdef __linux__
	pthread_setname_np(process->native_handle(),"wic video");
#endif
		}

		static void uninit()
		{
			running = false;
			if(!process)
				return;
			process->join();
			delete process;
			delete stream;
			process = 0;
			stream = 0;
		}

		static void add_processor(void (*f)(::video::frame))
		{ on_frame += f; }

		static void del_processor(void (*f)(::video::frame))
		{ on_frame -= f; }

	};

	template<typename c>
	::video::stream_reader *video<c>::stream = 0;

	template<typename c>
	std::thread *video<c>::process = 0;

	template<typename c>
	volatile bool video<c>::running = false;

	template<typename c>
	sched::event<::video::frame> video<c>::on_frame;
}
#endif
