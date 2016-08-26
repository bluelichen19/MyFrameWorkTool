#ifndef _CCTEST_H_
#define _CCTEST_H_
#include "codec_factory.h"
class CCTest
{
	public:
    CCodecFactory* ptrCC;
    CCTest();
    ~CCTest(){};
    void init();
};
#endif