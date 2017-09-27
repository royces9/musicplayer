CC = gcc
FLAGS = -lreadline -lSDL_mixer -lSDL -lncurses
HFILES = parse.h fileFuncs.h execFuncs.h struct.h musicFuncs.h playlistFuncs.h playList.h screen.h
CFILES = main.c parse.c fileFuncs.c execFuncs.c musicFuncs.c playlistFuncs.c playList.c screen.c
OFILES = musicFuncs.o execFuncs.o fileFuncs.o parse.o main.o playlistFuncs.o playList.o screen.o

mplayer: $(OFILES)
	$(CC) $(OFILES) -o musicplayer $(FLAGS)

execFuncs.o: execFuncs.c execFuncs.h fileFuncs.h musicFuncs.h struct.h playlistFuncs.h
	$(CC) -c execFuncs.c

fileFuncs.o: fileFuncs.c fileFuncs.h struct.h parse.h
	$(CC) -c fileFuncs.c

musicFuncs.o: musicFuncs.c musicFuncs.h
	$(CC) -c musicFuncs.c

parse.o: parse.c parse.h execFuncs.h struct.h screen.h
	$(CC) -c parse.c

playlistFuncs.o: playlistFuncs.c playlistFuncs.h musicFuncs.h
	$(CC) -c playlistFuncs.c

playList.o: playList.c playList.h
	$(CC) -c playList.c

screen.o: screen.c screen.h
	$(CC) -c screen.c

main.o: main.c parse.h
	$(CC) -c main.c

del:
	del $(OFILES)

exec: $(OFILES)
	$(CC) $(OFILES) -o musicplayer $(FLAGS) && ./musicplayer
