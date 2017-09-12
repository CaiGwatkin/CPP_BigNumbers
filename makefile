BigNumbers.exe	:	BigNumbers.o
	g++ BigNumbers.o -std=c++11 -o BigNumbers.exe

BigNumbers.o	:	BigNumbers.cpp BigNumbers.h
	g++ -std=c++11 -c BigNumbers.cpp

clean:
	del *.o
	del *.exe

