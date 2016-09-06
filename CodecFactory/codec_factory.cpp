#include "codec_factory.h"
#include "MediaCodec.h"

CCodecFactory* CCodecFactory::ptrCodecFactory = NULL;
CCodecFactory::GC CCodecFactory::gc;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

CCodecFactory* CCodecFactory::GetInstance(HW_CODEC_NUM hw_codec_num)
{
//	ScopeMutex scopeMutex(&mutex);
	if(!ptrCodecFactory)
	{
		switch(hw_codec_num)
		{
			case MEDIACODEC:
				ptrCodecFactory = new CMediaCodec();
				break;
			case STAGEFRIGHT:
				break;
			default:
				break;
		}
	}
	return ptrCodecFactory;
}
