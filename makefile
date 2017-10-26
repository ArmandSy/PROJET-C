all: PROJET EXECUTION

affichage.o: affichage.c affichage.h librairies.h
	gcc -c -Wall affichage.c
mouvements.o: mouvements.c mouvements.h librairies.h
	gcc -c -Wall mouvements.c
main.o: main.c affichage.h mouvements.h
	gcc -c -Wall main.c
PROJET: affichage.o mouvements.o main.o 
	gcc -o PROJET main.o affichage.o mouvements.o
EXECUTION: 
	./PROJET
