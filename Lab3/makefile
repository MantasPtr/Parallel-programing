defautl: compile run

compile:
	mpic++ src.cpp -o src
run:
	mpirun -n 2 ./src

serial_compile:
	g++ src_serial.cpp -o src_serial
serial_run:
	./src_serial
