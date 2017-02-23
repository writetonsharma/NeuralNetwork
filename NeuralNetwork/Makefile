CC=g++
CFLAGS=-O2


ann: CFile.o CMatrix.o CNeuralNetwork.o main.o CConfig.o partition.o preprocess.o algo.o
	$(CC) $(CFLAGS) -o ann CFile.o CMatrix.o CNeuralNetwork.o main.o CConfig.o partition.o preprocess.o algo.o
CFile.o: CFile.cpp
	$(CC) $(CFLAGS) -o CFile.o -c CFile.cpp
CMatrix.o: CMatrix.cpp
	$(CC) $(CFLAGS) -o CMatrix.o -c CMatrix.cpp
CNeuralNetwork.o: CNeuralNetwork.cpp
	$(CC) $(CFLAGS) -o CNeuralNetwork.o -c CNeuralNetwork.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp
CConfig.o: CConfig.cpp
	$(CC) $(CFLAGS) -o CConfig.o -c CConfig.cpp
partition.o: partition.cpp
	$(CC) $(CFLAGS) -o partition.o -c partition.cpp
preprocess.o: preprocess.cpp
	$(CC) $(CFLAGS) -o preprocess.o -c preprocess.cpp
algo.o: algo.cpp
	$(CC) $(CFLAGS) -o algo.o -c algo.cpp

debug:CFLAGS+=-g
debug:ann

clean: 
	rm *.o ann
