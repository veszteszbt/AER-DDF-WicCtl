#ifndef STREAM_READER
#define STREAM_READER

#include <stdio.h>
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
}

#include <video/frame.h>
#include <functional>
#include <journal.h>
#include <sched/listener.h>


namespace video {

struct stream_reader
{
    AVFormatContext *pFormatCtx = NULL;
    int             videoStream;
    AVCodecContext  *pCodecCtx = NULL;
    AVCodec         *pCodec = NULL;
    AVFrame         *pFrame = NULL; 
    AVFrame         *pFrameRGB = NULL;
    int             frameFinished;
    int             numBytes;
    uint8_t         *buffer = NULL;

    AVDictionary    *optionsDict = NULL;
    struct SwsContext      *sws_ctx = NULL;

    sched::event<frame> on_frame;

    static void av_log_handler(void* /*avcl*/,int severity,const char *format, va_list argptr)
    {
    	char *buf = new char[65536];
	vsnprintf(buf,65536,format,argptr);
	journal(journal::info,"video.avlib") << buf << journal::end;
	delete buf;	
    }

    stream_reader(const std::string& _stream)
    {
        avformat_network_init();
        av_register_all();
	av_log_set_callback(av_log_handler);

        //Open video file
        if(avformat_open_input(&pFormatCtx, _stream.c_str()/*"rtsp://admin:Almafa123@192.168.1.108:554"*/, NULL, NULL)!=0) { throw -1; }
        // Couldn't open file

        // Retrieve stream information
        if(avformat_find_stream_info(pFormatCtx, NULL)<0) {throw -1; }
        // Couldn't find stream information

        // Dump information about file onto standard error
        av_dump_format(pFormatCtx, 0, _stream.c_str()/*"rtsp://admin:Almafa123@192.168.1.108:554"*/, 0);

        // Find the first video stream
        videoStream=-1;
        for(int i=0; i<pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
        videoStream=i;
        break;
        }
        if(videoStream==-1) {throw -1; }
        // Didn't find a video stream

        // Get a pointer to the codec context for the video stream
        pCodecCtx=pFormatCtx->streams[videoStream]->codec;
    
        // Find the decoder for the video stream
        pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
        if(pCodec==NULL) 
        {
            fprintf(stderr, "Unsupported codec!\n");
            throw -1;
            // Codec not found
        }

        // Open codec
        if(avcodec_open2(pCodecCtx, pCodec, &optionsDict)<0) {throw -1; }
        // Could not open codec

        // Allocate video frame
        pFrame=av_frame_alloc();
    
        // Allocate an AVFrame structure
        pFrameRGB=av_frame_alloc();
        if(pFrameRGB==NULL) {throw -1; }

        // Determine required buffer size and allocate buffer
        numBytes=avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
        buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

        sws_ctx =
        sws_getContext
        (
            pCodecCtx->width,
            pCodecCtx->height,
            pCodecCtx->pix_fmt,
            pCodecCtx->width,
            pCodecCtx->height,
            AV_PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
        );

        // Assign appropriate parts of buffer to image planes in pFrameRGB
        // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
        // of AVPicture
        avpicture_fill((AVPicture *)pFrameRGB, buffer, AV_PIX_FMT_RGB24,
        pCodecCtx->width, pCodecCtx->height);

    }

    ~stream_reader()
    {
        // Free the RGB image
        av_free(buffer);
        av_free(pFrameRGB);
        
        // Free the YUV frame
        av_free(pFrame);
        
        // Close the codec
        avcodec_close(pCodecCtx);
        
        // Close the video file
        avformat_close_input(&pFormatCtx);
    }


    void process_frame()
    {

        AVPacket        packet;

        if (av_read_frame(pFormatCtx, &packet)<0)
            throw -1;
    
        // Is this a packet from the video stream?
        if(packet.stream_index==videoStream)
        {
            // Decode video frame
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, 
                    &packet);
            
            // Did we get a video frame?
            if(frameFinished)
            {
            // Convert the image from its native format to RGB
                sws_scale
                (
                    sws_ctx,
                    (uint8_t const * const *)pFrame->data,
                    pFrame->linesize,
                    0,
                    pCodecCtx->height,
                    pFrameRGB->data,
                    pFrameRGB->linesize
                );
        
                on_frame(frame(pCodecCtx->width, pCodecCtx->height, pFrameRGB));
            }
        }
        
        // Free the packet that was allocated by av_read_frame
        av_free_packet(&packet);
    }
};

}
#endif
