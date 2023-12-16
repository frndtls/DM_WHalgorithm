expToTT_test:expToTT_test.o expToTT.o operators.o
	g++ expToTT_test.o expToTT.o operators.o -o expToTT_test

expToTT_test.o:expToTT_test.cpp
	g++ -c expToTT_test.cpp -o expToTT_test.o

expToTT.o:expToTT.cpp
	g++ -c expToTT.cpp -o expToTT.o

operators.o:operators.cpp
	g++ -c operators.cpp -o operators.o

clean:
	del *.o *.exe