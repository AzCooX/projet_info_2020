OBJS	= main.o affichage.o fichiers.o fir.o iir.o integration.o lecture.o mesure.o
SOURCE	= main.c affichage.c fichiers.c fir.c iir.c integration.c lecture.c mesure.c
HEADER	= main.h affichage.h fichiers.h fir.h iir.h integration.h lecture.h mesure.h define.h
OUT	= projetCIR3
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

affichage.o: affichage.c
	$(CC) $(FLAGS) affichage.c

fichiers.o: fichiers.c
	$(CC) $(FLAGS) fichiers.c

fir.o: fir.c
	$(CC) $(FLAGS) fir.c

iir.o: iir.c
	$(CC) $(FLAGS) iir.c

integration.o: integration.c
	$(CC) $(FLAGS) integration.c

lecture.o: lecture.c
	$(CC) $(FLAGS) lecture.c

mesure.o: mesure.c
	$(CC) $(FLAGS) mesure.c


clean:
	rm -f $(OBJS) $(OUT)
