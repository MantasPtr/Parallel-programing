threadCount = 1 2 4

default: 
	@echo serial commands: doSerial, compileS, executeS,
	@echo parallel with rand\(\) commands: doParallelRand, compilePR, executePR
	@echo parallel witj rand_r\(\) commands: doParallelRandR, compilePRR, executePRR prrAll, executePRRAll

#status commands
echoThreads:
	@echo Thread count = $(threadCount)

#program execution

doSerial: compileS executeS

compileS:
	@g++ serial.cpp -o serial.o 

executeS: 
	@./serial.o

doParallelRand: compilePR executePR

compilePR:
	@g++ -fopenmp parallelRand.cpp -o pr.o

executePR: 
	@./pr.o\

doParallelRandR: compilePRR executePRR

compilePRR:
	@g++ -fopenmp parallelRandR.cpp -o prr.o\

executePRR: 
	@./prr.o\


prrAll: compilePRR executePRRAll 

executePRRAll: 
	@for t in $(threadCount); do \
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
		echo Thread count: $$t;\
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
		./prr.o $$t;\
		echo --------------------------------------;\
		./prr.o $$t;\
		echo --------------------------------------;\
		./prr.o $$t;\
		echo --------------------------------------;\
	done ;\
