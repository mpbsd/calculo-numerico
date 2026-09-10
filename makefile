CC     = cc
CLIBS  = -lc
CFLAGS = -g -W -Wall -Werror -Wextra -Wpedantic -std=c89

clear:
	find bin -type f -name "*.o" -delete

chase:
	valgrind -s --leak-check=full --show-leak-kinds=all ./bin/powerset.o -n 5

%:
	$(CC) $(CLIBS) $(CFLAGS) src/$@.c -o bin/$@.o

.PHONY: clear
