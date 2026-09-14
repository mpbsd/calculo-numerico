CC      = cc
CLIBS   = -lc
CFLAGS  = -g -W -Wall -Werror -Wextra -Wpedantic -std=c89
INCLUDE = -Ilib
SOURCES = lib/matrix.c

clear:
	find bin -type f -name "*.o" -delete

chase:
	valgrind -s --leak-check=full --show-leak-kinds=all ./bin/ludecomposition.o

%:
	$(CC) $(CLIBS) $(CFLAGS) $(INCLUDE) $(SOURCES) src/$@.c -o bin/$@.o

.PHONY: clear
