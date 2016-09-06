/* //device/libs/android_runtime/com_youku_uplayer_UUPlayer.cpp
**
** Copyright 2007, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define TAG "UEGL-JNI"

#include "uegl.h"

//#if !UCONFIG_NDK_EGL


// modified by bruce
//static const char* const kUEGLClassPathName = "com/youku/uplayer/EGLUtil";
char UEGL::kUEGLClassPathName[MAX_PATH_LENG] = "com/youku/uplayer/EGLUtil";
static const char* const kClassPathName = "com/youku/uplayer/EGLUtil";
static char* buf_decoder_free = NULL;
JavaVM *g_jvm = NULL;
void UEGL::setClassPath(const char *strClassPath) {
	int len = strlen(strClassPath);
	if(len >= MAX_PATH_LENG) {
		ulog_err("Error: %s is to long, truncate it", strClassPath);
		len = MAX_PATH_LENG - 1;
	}
	strlcpy(kUEGLClassPathName, strClassPath, len);
	kUEGLClassPathName[len] = '\0';
}

UEGL::UEGL(JNIEnv* env){

    jclass clazz = env->FindClass(kUEGLClassPathName);

    if (clazz == NULL) {
    	ulog_err("UEGL:FindClass failed: %s", kUEGLClassPathName);
        jniThrowException(env, "java/lang/RuntimeException", "Can't find EGLUtil");
        return;
    }
    mClass = (jclass)env->NewGlobalRef(clazz);

    if(!mClass){
    	ulog_err("UEGL:NewGlobalRef failed");
    }
    mInitEGL = (env)->GetStaticMethodID(mClass,"InitEGL","()Z");
    if(!mInitEGL){
    	ulog_err("UEGL:GetStaticMethodID InitEGL failed");
    }
    mReleaseEGLL = (env)->GetStaticMethodID(mClass,"ReleaseEGL","()V");
    if(!mReleaseEGLL){
    	ulog_err("UEGL:GetStaticMethodID ReleaseEGL failed");
    }
    mUpdateSurface = (env)->GetStaticMethodID(mClass,"UpdateSurface","()V");
    if(!mUpdateSurface){
    	ulog_err("UEGL:GetStaticMethodID UpdateSurface failed");
    }
    mUpdateSize = (env)->GetStaticMethodID(mClass,"UpdateSize","([I)V");
    if(!mUpdateSize){
    	ulog_err("UEGL:GetStaticMethodID UpdateSize failed");
    }
	mInitDecoder = (env)->GetStaticMethodID(mClass,"initWidthAndHeight","(II)V");
	if(!mInitDecoder){
		ulog_err("UEGL:GetStaticMethodID initWidthAndHeight failed");
	}
//	mDecodeSample = (env)->GetStaticMethodID(mClass,"decodeSample","([BI)V");
//	if(!mDecodeSample){
//		ulog_err("UEGL:GetStaticMethodID DecodeSample failed");
//	}
	mDecodeSample = (env)->GetStaticMethodID(mClass,"decodeSample","(IJ)V");
	if(!mDecodeSample){
		ulog_err("UEGL:GetStaticMethodID DecodeSample failed");
	}
		mGetDecoderBuffer = (env)->GetStaticMethodID(mClass,"getVideoBuffer","()Ljava/nio/ByteBuffer;");
	if(!mGetDecoderBuffer){
		ulog_err("UEGL:GetStaticMethodID getVideoBuffer failed");
	}
	mInitPPSSPS = (env)->GetStaticMethodID(mClass,"initDecoder","([BI[BI)V");
	if(!mInitPPSSPS){
		ulog_err("UEGL:GetStaticMethodID  initDecoder failed");
	}
	minitAudioDecoder = (env)->GetStaticMethodID(mClass,"initSampleRateAndChannel","(II)V");
	if(!minitAudioDecoder){
		ulog_err("UEGL:GetStaticMethodID initSampleRateAndChannel failed");
	}
//	mdecodeAudioSample = (env)->GetStaticMethodID(mClass,"decodeAudio","([BI)V");
//	if(!mdecodeAudioSample){
//		ulog_err("UEGL:GetStaticMethodID decodeAudio failed");
//	}
	mdecodeAudioSample = (env)->GetStaticMethodID(mClass,"decodeAudio","(I)V");
	if(!mdecodeAudioSample){
		ulog_err("UEGL:GetStaticMethodID decodeAudio failed");
	}
		mGetAudioBuffer = (env)->GetStaticMethodID(mClass,"getAudioBuffer","()Ljava/nio/ByteBuffer;");
	if(!mGetAudioBuffer){
		ulog_err("UEGL:GetStaticMethodID getAudioBuffer failed");
	}

	mInitESDS = (env)->GetStaticMethodID(mClass,"initAudioDecoder","([BI)V");
	if(!mInitPPSSPS){
		ulog_err("UEGL:GetStaticMethodID  initAudioDecoder failed");
	}
	mFlushMediaCodecBuffer = (env)->GetStaticMethodID(mClass,"flush","()V");
	if(!mFlushMediaCodecBuffer)
	{
		ulog_err("UEGL:GetStaticMethodID flush failed\n");
	}
	//pthread_mutex_init(&free_buff_mutex, NULL);
}
UEGL::~UEGL(){
    // remove global references
	int isAttacked=0;
	//pthread_mutex_destroy(&free_buff_mutex);
	JNIEnv *env = getJNIEnv(&isAttacked);
	if (env) {
		env->DeleteGlobalRef(mClass);

		if(isAttacked)
		{
			detachCurThread();
		}
	}
}
bool UEGL::InitEGL(){

	int isAttacked=0;

	ulog_info("UEGL:InitEGL enter");
	mJNIEnv = getJNIEnv(&isAttacked);

	if(!mJNIEnv){
		ulog_info("UEGL:InitEGL getJNIEnv failed");
		return false;
	}

	jboolean ret = (mJNIEnv)->CallStaticBooleanMethod(mClass,mInitEGL);

	if(isAttacked)detachCurThread();

	return ret;
}
void UEGL::ReleaseEGL(){

	int isAttacked=0;

	ulog_info("UEGL:ReleaseEGL enter");

	mJNIEnv = getJNIEnv(&isAttacked);

	if(!mJNIEnv)return;

	(mJNIEnv)->CallStaticVoidMethod(mClass,mReleaseEGLL);

	if(isAttacked)detachCurThread();
}

void UEGL::UpdateSurface(){

	int isAttacked=0;

	mJNIEnv = getJNIEnv(&isAttacked);

	if(!mJNIEnv)return;

	(mJNIEnv)->CallStaticVoidMethod(mClass,mUpdateSurface);

	if(isAttacked)detachCurThread();
}

void UEGL::UpdateSize(int *width,int *height){

	int isAttacked=0;

	mJNIEnv = getJNIEnv(&isAttacked);

	if(!mJNIEnv)return;

	jintArray size = (mJNIEnv)->NewIntArray(2);

	(mJNIEnv)->CallStaticVoidMethod(mClass,mUpdateSize,size);

	jint* psize = (mJNIEnv)->GetIntArrayElements(size, 0 );
	jsize len = (mJNIEnv)->GetArrayLength(size);

	if(len < 2){
		ulog_err("UEGL::UpdateSize len < 2");
	}

	*width = psize[0];
	*height = psize[1];

	(mJNIEnv)->ReleaseIntArrayElements(size, psize, 0 );
	(mJNIEnv)->DeleteLocalRef(size);

	if(isAttacked)detachCurThread();
}

//add by lichen

void UEGL::initDecoder(int width,int height)
{
	ulog_err("==MediaCodec==%s==%d==w is %d h is %d\n",__FUNCTION__,__LINE__,width,height); 
	int isAttacked = 0;
	mJNIEnv = getJNIEnv(&isAttacked);
	if(!mJNIEnv)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,mInitDecoder,width,height);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	if(isAttacked)detachCurThread();
}
void UEGL::decode_video(unsigned char* inputBuf, uint32_t len,uint64_t video_pts)
//void UEGL::decodeSample(char* inputBuf, uint32_t len)
{
	ulog_err("==MediaCodec==%s==%d====0x%08X====len is %d video_pts is %lld\n",__FUNCTION__,__LINE__,inputBuf,len,video_pts); 
	//pthread_mutex_lock(&free_buff_mutex);
	int tmp;
	unsigned char* decode_buffer = NULL;
	int isAttacked = 0;
	if(inputBuf == NULL || len == 0)
	{
		return;
	}
	for(tmp = 0;tmp<10;tmp++)
	{
		ulog_info("==inJNI Video Debug src is 0x%02X\n",inputBuf[tmp]);
	}
	//mJNIEnv = getJNIEnv(&isAttacked);
	mJNIEnv1 = getJNIEnv(&isAttacked);
	//if(!mJNIEnv)return;
	if(!mJNIEnv1)return;

	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//jobject result = (mJNIEnv)->CallStaticObjectMethod(mClass, mGetDecoderBuffer);
	jobject result = (mJNIEnv1)->CallStaticObjectMethod(mClass, mGetDecoderBuffer);
	//if((mJNIEnv)->ExceptionCheck())
	if((mJNIEnv1)->ExceptionCheck())
	{
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		//(mJNIEnv)->ExceptionClear();//清除异常
		(mJNIEnv1)->ExceptionClear();//清除异常
		//(mJNIEnv)->ExceptionDescribe();  //打印异常
		(mJNIEnv1)->ExceptionDescribe();  //打印异常
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		detachCurThread();
		return;
	}
	if(result == NULL)
	{
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		detachCurThread();
		return;
	}
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//decode_buffer = (unsigned char *) (mJNIEnv)->GetDirectBufferAddress(result);
	decode_buffer = (unsigned char *) (mJNIEnv1)->GetDirectBufferAddress(result);
	if(decode_buffer == NULL)
	{
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		detachCurThread();
		return;
	}	
	//if((mJNIEnv)->ExceptionCheck())
	if((mJNIEnv1)->ExceptionCheck())
	{
		//(mJNIEnv)->ExceptionClear();//清除异常
		(mJNIEnv1)->ExceptionClear();//清除异常
		//(mJNIEnv)->ExceptionDescribe();  //打印异常
		(mJNIEnv1)->ExceptionDescribe();  //打印异常
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		detachCurThread();
		return;
	}
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//memset(decode_buffer,'\0',len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	memcpy(decode_buffer,inputBuf,len);
	decode_buffer[0] = 0x00;
	decode_buffer[1] = 0x00;
	decode_buffer[2] = 0x00;
	decode_buffer[3] = 0x01;
	for(tmp = 0;tmp<10;tmp++)
	{
		ulog_info("==inJNI Video Debug dst is 0x%02X\n",decode_buffer[tmp]);
	}
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//(mJNIEnv)->CallStaticVoidMethod(mClass,mDecodeSample,len,video_pts);
	(mJNIEnv1)->CallStaticVoidMethod(mClass,mDecodeSample,len,video_pts);
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
		detachCurThread();
		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
//	if(isAttacked){
//		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
//		detachCurThread();
//		ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
//	}
#if 0
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	jbyteArray array = (mJNIEnv)->NewByteArray(len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//(mJNIEnv)->CallStaticVoidMethod(mClass,decodeSample,width,height);
			buf_decoder_free = inputBuf;
	(mJNIEnv)->SetByteArrayRegion(array,0,len,(jbyte*)inputBuf);	
	ulog_err("jbytearray is 0x%08X Cbuf is 0x%08X\n",array,inputBuf);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,mDecodeSample,array,len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	ulog_err("free decoder buf1\n");
//	   if(inputBuf){
//		ulog_err("free decoder buff ok\n");
//		free(inputBuf);
//		inputBuf = NULL;
//	}
	//jbyte *dst = (mJNIEnv)->GetByteArrayElements(array, NULL);
	//(mJNIEnv)->ReleaseByteArrayElements(array, dst, 0);
	//dst = NULL;
	(mJNIEnv)->DeleteLocalRef(array);
	ulog_err("free decoder buf2\n");
	if(isAttacked)detachCurThread();
#endif
	//pthread_mutex_unlock(&free_buff_mutex);
}
void UEGL::initPPSSPS(char* sps_buffer, uint32_t sps_size,char* pps_buffer,uint32_t pps_size)
{
	int isAttacked = 0;
	mJNIEnv = getJNIEnv(&isAttacked);
	if(!mJNIEnv)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	ulog_info("PPSSPS sps line is %d==pps line is %d,\n",sps_size,pps_size);
	int tmp;
	for(tmp = 0;tmp<sps_size;tmp++)
	{
		ulog_info("==sps is 0x%02X ",sps_buffer[tmp]);
	}
	for(tmp = 0;tmp<pps_size;tmp++)
	{
		ulog_info("==pps is 0x%02X ",pps_buffer[tmp]);
	}
	jbyteArray sps_array = (mJNIEnv)->NewByteArray(sps_size);
	jbyteArray pps_array = (mJNIEnv)->NewByteArray(pps_size);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//(mJNIEnv)->CallStaticVoidMethod(mClass,decodeSample,width,height);
	(mJNIEnv)->SetByteArrayRegion(sps_array,0,sps_size,(jbyte*)sps_buffer);	
	(mJNIEnv)->SetByteArrayRegion(pps_array,0,pps_size,(jbyte*)pps_buffer);	
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,mInitPPSSPS,sps_array,sps_size,pps_array,pps_size);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	if(isAttacked)detachCurThread();
}

void UEGL::initAudioDecoder(int sample_rate, int channels)
{
	ulog_err("==MediaCodec==%s==%d==rate is %d channels is %d\n",__FUNCTION__,__LINE__,sample_rate,channels); 
	int isAttacked = 0;
	mJNIEnv = getJNIEnv(&isAttacked);
	if(!mJNIEnv)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,minitAudioDecoder,sample_rate,channels);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	if(isAttacked)detachCurThread();
}

void UEGL::decodeAudioSample(char* inputBuf, uint32_t len)
{
#if 0
	ulog_err("==MediaCodec==%s==%d====0x%08X====len is %d\n",__FUNCTION__,__LINE__,inputBuf,len); 
	int tmp;
	unsigned char* decode_buffer = NULL;
	for(tmp = 0;tmp<10;tmp++)
	{
		ulog_info("==inJNI Audio Debug is 0x%02X\n",inputBuf[tmp]);
	}
	int isAttacked = 0;
	mJNIEnv = getJNIEnv(&isAttacked);
	if(!mJNIEnv)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	jbyteArray array = (mJNIEnv)->NewByteArray(len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
			buf_decoder_free = inputBuf;
	(mJNIEnv)->SetByteArrayRegion(array,0,len,(jbyte*)inputBuf);	
	ulog_err("jbytearray is 0x%08X Cbuf is 0x%08X\n",array,inputBuf);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,mdecodeAudioSample,array,len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	ulog_err("free decoder buf3\n");
	//jbyte *dst = (mJNIEnv)->GetByteArrayElements(array, NULL);
	//(mJNIEnv)->ReleaseByteArrayElements(array, dst, 0);
	//dst = NULL;
	(mJNIEnv)->DeleteLocalRef(array);
	ulog_err("free decoder buf4\n");
	if(isAttacked)detachCurThread();
#endif
	ulog_err("==MediaCodec==%s==%d====0x%08X====len is %d\n",__FUNCTION__,__LINE__,inputBuf,len); 
	//pthread_mutex_lock(&free_buff_mutex);
	int tmp;
	unsigned char* decode_buffer = NULL;
	for(tmp = 0;tmp<10;tmp++)
	{
		ulog_info("==inJNI Audio Debug src is 0x%02X\n",inputBuf[tmp]);
	}
	int isAttacked = 0;
	//mJNIEnv = getJNIEnv(&isAttacked);
	mJNIEnv1 = getJNIEnv(&isAttacked);
	//if(!mJNIEnv)return;
	if(!mJNIEnv1)return;

	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//jobject result = (mJNIEnv)->CallStaticObjectMethod(mClass, mGetAudioBuffer);
	jobject result = (mJNIEnv1)->CallStaticObjectMethod(mClass, mGetAudioBuffer);

	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//decode_buffer = (unsigned char *) (mJNIEnv)->GetDirectBufferAddress(result);
	decode_buffer = (unsigned char *) (mJNIEnv1)->GetDirectBufferAddress(result);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//memset(decode_buffer,'\0',len);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	memcpy(decode_buffer,inputBuf,len);
	for(tmp = 0;tmp<10;tmp++)
	{
		ulog_info("==inJNI Audio Debug dst is 0x%02X\n",decode_buffer[tmp]);
	}
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//(mJNIEnv)->CallStaticVoidMethod(mClass,mdecodeAudioSample,len);
	(mJNIEnv1)->CallStaticVoidMethod(mClass,mdecodeAudioSample,len);
	if(isAttacked)
		detachCurThread();

}

void UEGL::initESDS(char* ESDS_buffer, uint32_t size)
{
	int isAttacked = 0;
	mJNIEnv = getJNIEnv(&isAttacked);
	if(!mJNIEnv)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	int tmp;
	for(tmp = 0;tmp<size;tmp++)
	{
		ulog_info("==ESDS is 0x%02X size is %d\n",ESDS_buffer[tmp],size);
	}
	jbyteArray ESDS_array = (mJNIEnv)->NewByteArray(size);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	//(mJNIEnv)->CallStaticVoidMethod(mClass,decodeSample,width,height);
	(mJNIEnv)->SetByteArrayRegion(ESDS_array,0,size,(jbyte*)ESDS_buffer);	
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv)->CallStaticVoidMethod(mClass,mInitESDS,ESDS_array,size);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	if(isAttacked)detachCurThread();
}
void UEGL::flush_media_codec_buffer()
{
	int isAttacked = 0;
	mJNIEnv_flush = getJNIEnv(&isAttacked);
	if(!mJNIEnv_flush)return;
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	(mJNIEnv_flush)->CallStaticVoidMethod(mClass,mFlushMediaCodecBuffer);
	ulog_err("==MediaCodec==%s==%d\n",__FUNCTION__,__LINE__); 
	if(isAttacked)detachCurThread();
}

void UEGL::free_decoder_buff()
{
	return;
//	ulog_err("free decoder buf1\n");
//	pthread_mutex_lock(&free_buff_mutex);
//   	if(buf_decoder_free){
//		ulog_err("free decoder buff ok\n");
//		free(buf_decoder_free);
//		buf_decoder_free = NULL;
//	}
//	pthread_mutex_unlock(&free_buff_mutex);
//	ulog_err("free decoder buf2\n");
}
//#endif

