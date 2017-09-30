nsize = 24000 48000 96000
default: compile executeN

echoN:
	echo $(nsize)

compile:
	g++ -fopenmp algorithm.cpp -o program #

execute: program
	./program  #
	./program #
	./program #

executeN: program
	for n in $(nsize); do \
		echo N size: $$n; \
		./program $$n ;\
		./program $$n ;\
		./program $$n ;\
		echo -------------------------------------;\
	done; \
