all: main

main: main.o graph.o tsp.o

%.o: %.c
        $(CROSS_COMPILE)$(CC) -c $^ -o $@ -g
