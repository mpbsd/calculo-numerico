CC     = cc
CLIBS  = -lc
CFLAGS = -g -W -Wall -Werror -Wextra -Wpedantic -std=c89

clear:
	find bin -type f -name "*.o" -delete

%:
	$(CC) $(CLIBS) $(CFLAGS) src/$@.c -o bin/$@.o

.PHONY: clear
