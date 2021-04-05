CC = gcc
FLAGS = -g -std=gnu99
OBJ = atob.o btoa.o jabber.o wocky.o
EXEC = atob btoa jabber wocky test-me
TEST_ASCII = hollow

all: $(EXEC)

test-me: jabber wocky atob btoa
	./atob $(TEST_ASCII).txt bit-$(TEST_ASCII).txt;
	./jabber bit-$(TEST_ASCII).txt zap-$(TEST_ASCII).txt;
	./wocky zap-$(TEST_ASCII).txt kapow-$(TEST_ASCII).txt;
	./btoa kapow-$(TEST_ASCII).txt out.txt;
	diff $(TEST_ASCII).txt out.txt

jabber: jabber.o list.c
	$(CC) $(FLAGS) -o jabber jabber.o list.c

wocky: wocky.o list.c
	$(CC) $(FLAGS) -lm -o wocky wocky.o list.c

atob: atob.o
	$(CC) $(FLAGS) -o atob atob.o

btoa: btoa.o
	$(CC) $(FLAGS) -lm -o btoa btoa.o

jabber.o: jabber.c
	$(CC) $(FLAGS) -c jabber.c

wocky.o: wocky.c
	$(CC) $(FLAGS) -c wocky.c

atob.o: atob.c
	$(CC) $(FLAGS) -c atob.c

btoa.o: btoa.c
	$(CC) $(FLAGS) -c btoa.c

clean:
	rm -f $(OBJ) $(EXEC) bit-$(TEST_ASCII).txt zap-$(TEST_ASCII).txt kapow-$(TEST_ASCII).txt out.txt
