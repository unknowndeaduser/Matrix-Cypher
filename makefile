brog: main.o entite.o tic.o
	gcc main.o entite.o tic.o -o brog -lSDL -lSDL_image -lSDL_ttf

main.o: main.c
	gcc -c main.c -g

entite.o: entite.c
	gcc -c entite.c -g

tic.o: tic.c
	gcc -c tic.c -g
