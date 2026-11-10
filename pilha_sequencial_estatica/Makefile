CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: pilha_sequencial.o main.o
	$(CC) $(CFLAGS) -o teste pilha_sequencial.o main.o

PilhaSequencial.o: pilha_sequencial.c pilha_sequencial.h
	$(CC) $(CFLAGS) -c pilha_sequencial.c

main.o: main.c pilha_sequencial.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste