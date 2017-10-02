# Program that prints out number of threads in you computer

### Requirements

- Have gcc compiler
- Have openMP library installed

### Usage:
``` 
1. Open cmd
2. Type make
```
or alternatively

1. Open cmd
2. Type ```g++ -fopenmp threadCount.cpp -o counter``` to compile
3  Type ```./counter``` to run

### Result:

Program will output this to your console:

```thread count = N```,
where N is thread count on your system.

#### Possible problems:
This was only tested on shared memory computers. Not sure if this works on distributed memory computers.