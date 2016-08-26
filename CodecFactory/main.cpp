#include <iostream>
#include "codec_factory.h"
#include "base.h"
#include "CCTest.h"
int main(int argc, char* argv[])
{
#if 1
    printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
	CCTest* mtest = new CCTest();	
	printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
    mtest->init();
    delete mtest;
	printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
	return 0;
#endif
#if 0
    int width = 360;
    int height = 480;
    CCodecFactory *factoryA = CCodecFactory::GetInstance(MEDIACODEC);
    printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
    factoryA->set_video_parameter(width,height);
    printf("debug==line:%d function:%s flie:%s\n",__LINE__,__FUNCTION__,__FILE__);
#endif
}
