OBJS = bashInt.o scanner.o string.o da.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all:	bashInt

bashInt:	$(OBJS)
	gcc $(LOPTS) -o bashInt $(OBJS)

bashInt.o: scanner.h string.h da.h bashInt.c
	gcc $(OOPTS) bashInt.c

scanner.o:	scanner.h scanner.c
	gcc $(OOPTS) scanner.c

string.o:	string.h string.c
	gcc $(OOPTS) string.c

da.o:	da.h da.c
	gcc $(OOPTS) da.c

clean:
	rm $(OBJS) bashInt
