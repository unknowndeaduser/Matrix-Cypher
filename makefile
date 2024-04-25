brog:main.o tic.o
	gcc main.o tic.o -o brog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.o:main.c
	gcc -c main.c -g

entite.o:tic.c
	gcc -c tic.c -g


