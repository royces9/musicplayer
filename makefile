CC = gcc
FLAGS = 
HEADERS = -lreadline
CFILES = main.c

name: $(HEADERS)
	$(CC) -o NAME $(CFILES) $(FLAGS)
