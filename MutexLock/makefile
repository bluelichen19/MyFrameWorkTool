main:BlueSourceLog.o BlueMutexLock.o test.o 
	g++ BlueSourceLog.o BlueMutexLock.o test.o  -lpthread -g -o main
BlueMutexLock.o : BlueMutexLock.h ../DebugTrace/BlueDebugTrace.cpp
	g++ -g -c BlueMutexLock.cpp
BlueSourceLog.o : ../DebugTrace/BlueSourceLog.h ../DebugTrace/BlueSourceLog.cpp ../DebugTrace/BlueDebugTrace.h
	g++ -g -c ../DebugTrace/BlueSourceLog.cpp
test.o : BlueMutexLock.h test.cpp
	g++ -g -c test.cpp
.PHONY : clean 
clean : rm ./*.o test 
