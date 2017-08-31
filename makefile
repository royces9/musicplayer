CC = gcc
FLAGS = -lreadline
HEADERS = parse.h m3ucopy.h m3ufuncs.h fileFuncs.h execFuncs.h struct.h
CFILES = main.c parse.c m3ucopy.c m3ufuncs.c fileFuncs.c execFuncs.c

name: $(HEADERS)
	$(CC) -o musicplayer $(CFILES) $(FLAGS)
