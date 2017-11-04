threadCount = 1 2 4

default: compile executeAll

standart:
	g++ -fopenmp main.cpp -o main
	./main


#status commands
echoThreads:
	@echo Thread count = $(threadCount)

#program execution

compile:
	@g++ -fopenmp main.cpp -o main

execute: 
	./main 
	
executeAll: 
	@for t in $(threadCount); do \
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
		echo Thread count: $$t;\
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
		./main $$t;\
		echo --------------------------------------;\
		./main $$t;\
		echo --------------------------------------;\
		./main $$t;\
		echo --------------------------------------;\
	done ;\

compileSerial:
    @g++ -fopenmp serial.cpp -o serial
executeSerial:
    ./serial
doSerial: compileSerial executeSerial
