threadCount = 1 2 4

default: 
	@echo serial with rand\(\) commands: doSerialRand, compileSR, executeSR,
	@echo parallel with rand\(\) commands: doParallelRand, compilePR, executePR
	@echo serial with rand_r\(\) commands: doSerialRandR, compileSRR, executeSRR,
	@echo parallel with rand_r\(\) commands: doParallelRandR, compilePRR, executePRR prrAll, executePRRAll
	
#status commands
echoThreads:
	@echo Thread count = $(threadCount)

#program execution

doSerialRand: compileSR executeSR

compileSR:
	@g++ serialRand.cpp -o sr.o 

executeSR: 
	@./sr.o

doSerialRandR: compileSRR executeSRR

compileSRR:
	@g++ serialRandR.cpp -o srr.o

executeSRR: 
	@./srr.o

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
