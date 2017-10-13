#ifndef SOUNDSTREAM_H
# define SOUNDSTREAM_H
# include <iostream>
# include <cstdint>
# include <numeric>
# include <sndfile.hh>

class soundbuf : public std::basic_streambuf<int16_t>
{
	typedef std::basic_streambuf<int16_t> base;

	SndfileHandle handle;

	const std::string &path;

	int16_t *framebuf;

	uint8_t channels;
public:

	soundbuf(const std::string &ppath)
		: std::basic_streambuf<int16_t>()
		, handle(ppath.c_str())
		, path(ppath)
	{
		channels = static_cast<uint8_t>(handle.channels());
		framebuf = new int16_t[channels];
	}

	virtual ~soundbuf()
	{ delete framebuf; }

	virtual pos_type seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in)
	{ return static_cast<off_type>(handle.seek(static_cast<sf_count_t>(off),static_cast<int>(way))); }

	virtual pos_type seekpos(pos_type pos, std::ios_base::openmode which = std::ios_base::in)
	{ return handle.seek(pos,static_cast<int>(std::ios_base::beg)); }
	
	virtual std::streamsize showmanyc()
	{ return static_cast<std::streamsize>(handle.frames()-handle.seek(0,std::ios_base::cur)); }

	virtual std::streamsize xsgetn(char_type *s, std::streamsize n)
	{
		for(std::streamsize i = 0; i < n; ++i)
		{
			const sf_count_t res = handle.readf(framebuf,1);

			if(res == 0)
				return i;

			*s++ = static_cast<int16_t>(std::accumulate(framebuf,&framebuf[channels],0)/channels);
		}
		return n;
	}
};

class isoundstream : public std::basic_istream<int16_t> 
{
	soundbuf _sb;

public:
	isoundstream(const std::string &path)
		: std::basic_istream<int16_t>()
		, _sb(path)
	{ rdbuf(&_sb); }

	virtual ~isoundstream()
	{}
};

#endif
