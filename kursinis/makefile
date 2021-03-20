default: full
gcc: compile run
full: compile run scale preview
# compile:
# 	mpic++ src.cpp -o src.sh
# run:
# 	mpirun -n 2 ./src.sh

compile:
	g++ src.cpp -o program.sh
run:
	./program.sh
scale:
	convert image.pgm -scale 1000x result.png
preview:
	eog result.png