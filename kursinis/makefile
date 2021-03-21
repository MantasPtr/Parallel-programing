default: full
gcc: compile run
full: cleanup compile run gif preview
# compile:
# 	mpic++ src.cpp -o src.sh
# run:
# 	mpirun -n 2 ./src.sh
cleanup:
	rm -rf ./images/*

compile:
	g++ src.cpp -o program.sh
run:
	./program.sh
scale1:
	convert -scale 1000x  -delay 10 -loop 0 image_0.pgm $(for i in $(seq 0 50 9950); do echo image_${i}.pgm; done) images/result.gif 
gif:
	convert -scale 1000x  -delay 10 -loop 0 images/*.pgm images/result.gif 
preview:
	eog images/result.gif