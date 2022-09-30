CC=gcc
CFLAGS=-g -Wall -I./include
TARGET=main
OBJS=Vector3.o MollerTrumbore.o main.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

Vector3.o: src/Vector3.c
	$(CC) $(CFLAGS) -c $^ -o $@

MollerTrumbore.o: src/MollerTrumbore.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf main $(OBJS)
