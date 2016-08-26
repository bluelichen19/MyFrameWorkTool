#ifndef _CODEC_FACTORY_H_
#define _CODEC_FACTORY_H_

#include <iostream>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "base.h"

//class ScopeMutex{
//	public:
//		ScopeMutex(pthread_mutex_t* mutex):mutex_(&mutex){
//			pthread_mutex_lock(&mutex_ );
//		}
//		~ScopeMutex(){
//			pthread_mutex_unlock(&mutex_ );
//		}
//	private:
//		pthread_mutex_t *mutex_;
//};
//
class CCodecFactory
{
	public:
		static CCodecFactory* GetInstance(HW_CODEC_NUM codec_num);
		virtual int init_video_decoder(unsigned video_extradata) = 0;
		virtual int init_audio_decoder(unsigned audio_extradata) = 0;
		virtual int set_video_parameter(int width, int height) = 0;
		virtual int set_audio_parameter(int sample_rate, int channel) = 0;
		virtual int decoder_video(unsigned video_buffer, uint64_t buffer_size, uint64_t pts) = 0;
		virtual int decoder_audio(unsigned audio_buffer, uint64_t buffer_size, uint64_t pts) = 0;
	private:
		static CCodecFactory* ptrCodecFactory;
		class GC
		{
			public:
                GC()
            {
                printf("new gc\n");
            }
				~GC()
				{
					if(ptrCodecFactory)
					{
						printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
						delete ptrCodecFactory;
						printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
						ptrCodecFactory = NULL;
						printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
					}
				}
		};
		static GC gc;
	protected:
		CCodecFactory(){};
		virtual ~CCodecFactory(){};
};
#endif
