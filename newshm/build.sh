g++ -c shmfifo.cpp shmfifo.h 
g++ -c get.c 
g++ -c put.c
g++ get.o shmfifo.o -o get
g++ put.o shmfifo.o -o put

