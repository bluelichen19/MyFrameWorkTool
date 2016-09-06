#include "CCTest.h"
CCTest::CCTest()
{
    ptrCC = NULL;
}
void CCTest::init()
{
    int width = 360;
    int height = 480;
    //CCodecFactory *factoryA = CCodecFactory::GetInstance(MEDIACODEC);
    //factoryA->set_video_parameter(width,height);
    ptrCC = CCodecFactory::GetInstance(MEDIACODEC);
    ptrCC->set_video_parameter(width,height);
}