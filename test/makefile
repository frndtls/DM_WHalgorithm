all: expToTT_test expToPar_test ttToExp_test boilDownInference_test WHalgorithm_test

expToTT_test:expToTT_test.o expToTT.o operators.o
	g++ $^ -o $@

expToPar_test:expToPar_test.o expToPar.o  expToTT.o operators.o 
	g++ $^ -o $@

ttToExp_test:ttToExp_test.o expToPar.o expToTT.o operators.o
	g++ $^ -o $@

boilDownInference_test:boilDownInference_test.o expToTT.o expToPar.o operators.o boilDownInference.o
	g++ $^ -o $@

WHalgorithm_test: WHalgorithm_test.o expToTT.o  operators.o WHalgorithm.o
	g++ $^ -o $@

WHalgorithm_test.o:WHalgorithm_test.cpp
	g++ -c $^ -o $@

WHalgorithm.o:../header/WHalgorithm.cpp
	g++ -c $^ -o $@

boilDownInference.o:../header/boilDownInference.cpp
	g++ -c $^ -o $@

ttToExp_test.o:ttToExp_test.cpp
	g++ -c $^ -o $@

expToPar_test.o:expToPar_test.cpp
	g++ -c $^ -o $@

expToPar.o:../header/expToPar.cpp
	g++ -c $^ -o $@

expToTT_test.o:expToTT_test.cpp
	g++ -c $^ -o $@

expToTT.o:../header/expToTT.cpp
	g++ -c $^ -o $@

operators.o:../header/operators.cpp
	g++ -c $^ -o $@
	
clean:
	rm *.o *.exe