#ifndef _MEDIA_CODEC_H_
#define _MEDIA_CODEC_H_

#include "codec_factory.h"

class CMediaCodec:public CCodecFactory
{
	friend class CCodecFactory;
	public:
		int init_video_decoder(unsigned video_extradata);
		int init_audio_decoder(unsigned audio_extradata);
		int set_video_parameter(int width, int height);
		int set_audio_parameter(int sample_rate, int channel);
		int decoder_video(unsigned video_buffer, uint64_t buffer_size, uint64_t pts);
		int decoder_audio(unsigned audio_buffer, uint64_t buffer_size, uint64_t pts);
	protected:
		CMediaCodec(){};
		virtual ~CMediaCodec();
};
#endif
