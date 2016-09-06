main:BlueSourceLog.o BlueDebugTrace.o test.o 
	g++ BlueSourceLog.o BlueDebugTrace.o test.o -g -o main
BlueDebugTrace.o : BlueDebugTrace.h
	g++ -g -c BlueDebugTrace.cpp
BlueSourceLog.o : BlueSourceLog.h
	g++ -g -c BlueSourceLog.cpp
test.o : BlueSourceLog.h BlueDebugTrace.h
	g++ -g -c test.cpp
.PHONY : clean 
clean : rm ./*.o test 
