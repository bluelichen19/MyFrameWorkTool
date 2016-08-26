edit : main.o codec_factory.o MediaCodec.o CCTest.o
	g++ -o edit main.o codec_factory.o MediaCodec.o CCTest.o
main.o : main.cpp base.h codec_factory.h CCTest.h
	g++ -c main.cpp
codec_factory.o : codec_factory.cpp codec_factory.h base.h MediaCodec.h
	g++ -c codec_factory.cpp
MediaCodec.o : MediaCodec.cpp codec_factory.h MediaCodec.h
	g++ -c MediaCodec.cpp
CCTest.o	:	CCTest.cpp codec_factory.h
	g++ -c CCTest.cpp	
clean :
	rm edit main.o codec_factory.o MediaCodec.o

