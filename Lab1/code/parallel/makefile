nSize = 24000 48000 96000
threadCount = 1 2 4

default: compile executeAll

#status commands
echoN:
	@echo N = $(nSize)

echoThreads:
	@echo Thread count = $(threadCount)

echoParams: echoN echoThreads

#program execution

compile:
	g++ -fopenmp algorithm.cpp -o program 

execute: program
	./program 
	./program 
	./program 

executeAll: 
	@for t in $(threadCount); do \
		echo Thread count: $$t;\
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
		for n in $(nSize); do\
			echo N size: $$n;\
			echo --------------------------------------;\
			./program $$n $$t;\
			./program $$n $$t;\
			./program $$n $$t;\
			echo --------------------------------------;\
		done; \
		echo \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#;\
	done ;\
