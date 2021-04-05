CC = gcc
SRC = formatter
EXEC = formatter
TEXT = shakespeare

all: $(EXEC) test-me

$(EXEC): $(SRC).o list.c
	$(CC) -g -std=c99 -o $(EXEC) $(SRC).o list.c

$(SRC).o: $(SRC).c
	$(CC) -g -std=c99 -c $(SRC).c

test-me:
	./$(EXEC) $(TEXT).txt out.txt 50

clean:
	rm -f $(EXEC) $(SRC).o
