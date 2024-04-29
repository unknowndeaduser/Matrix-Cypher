brog:main.o entite.o
	gcc main.o entite.o -o brog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.o:main.c
	gcc -c main.c -g

entite.o:entite.c
	gcc -c entite.c -g


