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

		static void start()
		{
			stream = new ::video::stream_reader(TConfig::cfg_source);

			while(running)
				stream->process_frame();

			delete stream;
		}

	public:
		static void init()
		{
			running = true;
			process = new std::thread(start);
		}

		static void uninit()
		{
			running = false;
			if(!process)
				return;
			process->join();
			delete process;
			process = 0;
		}

		static void add_processor(void (*f)(::video::frame))
		{ stream->on_frame += f; }

		static void del_processor(void (*f)(::video::frame))
		{ stream->on_frame -= f; }

	};

	template<typename c>
	::video::stream_reader *video<c>::stream;

	template<typename c>
	std::thread *video<c>::process;

	template<typename c>
	volatile bool video<c>::running;
}
#endif
