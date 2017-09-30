nSize = 24000 48000 96000

default: compile executeAll

#status commands
echoN:
	@echo N = $(nSize)

echoParams: echoN
	@echo serial execetion only uses 1 thread

#program execution

compile:
	g++ algorithm.cpp -o program 

execute: program
	./program 
	./program 
	./program 

executeAll:
	@for n in $(nSize); do \
		echo N size: $$n; \
		./program $$n ;\
		./program $$n ;\
		./program $$n ;\
		echo -------------------------------------;\
	done; \
