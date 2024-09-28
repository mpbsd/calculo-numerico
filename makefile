CC     = cc
CFLAGS = -g -W -Wall -Wextra -Wpedantic -std=c89
CLIBS  = -lc

build:
	python3 -m pkgs.core

black:
	isort pkgs/core.py
	black -l 79 pkgs/core.py

clang:
	$(CC) $(CFLAGS) $(CLIBS) pkgs/main.c -o main.o && ./main.o

chase:
	valgrind --leak-check=full --show-leak-kinds=all ./main.o

clean:
	find . -type d -name __pycache__ -delete
	find bin -type f -name "*.o" -delete

ready:
	python3 -m venv venv; \
	. venv/bin/activate; \
	pip install -U pip; \
	pip install -r requirements.txt; \
	deactivate

.PHONY: build black clang clean ready
