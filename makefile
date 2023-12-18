all: expToTT_test expToPar_test ttToExp_test boilDownInference_test

expToTT_test:expToTT_test.o expToTT.o operators.o
	g++ $^ -o $@

expToPar_test:expToPar_test.o expToPar.o  expToTT.o operators.o 
	g++ $^ -o $@

ttToExp_test:ttToExp_test.o expToPar.o expToTT.o operators.o
	g++ $^ -o $@

boilDownInference_test:boilDownInference_test.o expToTT.o expToPar.o operators.o boilDownInference.o
	g++ $^ -o $@
boilDownInference.o:boilDownInference.cpp
	g++ -c $^ -o $@

ttToExp_test.o:ttToExp_test.cpp
	g++ -c $^ -o $@

expToPar_test.o:expToPar_test.cpp
	g++ -c $^ -o $@

expToPar.o:expToPar.cpp
	g++ -c $^ -o $@

expToTT_test.o:expToTT_test.cpp
	g++ -c $^ -o $@

expToTT.o:expToTT.cpp
	g++ -c $^ -o $@

operators.o:operators.cpp
	g++ -c $^ -o $@
	
clean:
	del *.o *.exe