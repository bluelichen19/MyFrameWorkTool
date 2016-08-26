#include "MediaCodec.h"

CMediaCodec::~CMediaCodec()
{
	printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
}
int CMediaCodec::init_video_decoder(unsigned video_extradata)
{
	return 0;
}
int CMediaCodec::init_audio_decoder(unsigned audio_extradata)
{
	return 0;
}
int CMediaCodec::set_video_parameter(int width, int height)
{
						printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
	return 0;
}
int CMediaCodec::set_audio_parameter(int sample_rate, int channel)
{
	return 0;
}
int CMediaCodec::decoder_video(unsigned video_buffer, uint64_t buffer_size, uint64_t pts)
{
	return 0;
}
int CMediaCodec::decoder_audio(unsigned audio_buffer, uint64_t buffer_size, uint64_t pts)
{
	return 0;
}

