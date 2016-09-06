main:BlueSourceLog.o BlueDebugTrace.o test.o 
	g++ BlueSourceLog.o BlueDebugTrace.o test.o -g -o main
BlueDebugTrace.o : BlueDebugTrace.h BlueDebugTrace.cpp
	g++ -g -c BlueDebugTrace.cpp
BlueSourceLog.o : BlueSourceLog.h BlueSourceLog.cpp
	g++ -g -c BlueSourceLog.cpp
test.o : BlueSourceLog.h BlueDebugTrace.h test.cpp
	g++ -g -c test.cpp
.PHONY : clean 
clean : rm ./*.o test 
