defautl: compile run

compile:
	mpic++ src.cpp -o src.sh
run:
	mpirun -n 2 ./src.sh

serial_compile:
	g++ src_serial.cpp -o src_serial.sh
serial_run:
	./src_serial.sh
