### VARIABLES ###
 
CC = gcc
CFLAGS = -Wall \
        -ansi \
         -pedantic
         
LIBS = -lgraph
EXE = exe
OFILES = main.o \
         graphique.o \
         jeu.o \
         utilitaires.o \
      
 
### BUT PAR DEFAUT ###
 
but : ${EXE}

### REGLES ESSENTIELLES ###

${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES} ${LIBS} 


main.o : graphique.h jeu.h utilitaires.h

jeu.o : jeu.h utilitaires.h graphique.h 

graphique.o : graphique.h

utilitaires.o : utilitaires.h

### REGLES OPTIONNELLES ###

run : but
	./${EXE}

clean :
	-rm -f ${OFILES} ${EXE}

mrproper : clean but
 
### BUTS FACTICES ###
 
.PHONY : but clean mrproper
 
### FIN ###