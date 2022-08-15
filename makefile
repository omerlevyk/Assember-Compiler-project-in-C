main.o : main.c macroManager.h firstRun.h
	gcc -g -ansi -Wall -pedantic main.c -o main.o
LineManager.o : LineManager.c LinesManager.h
	gcc -g -ansi -Wall -pedantic LineManager.c -o LineManager.o
macroManager.o : macroManager.c macroManager.h
	gcc -g -ansi -Wall -pedantic macroManager.c -o macroManager.o
firstRun.o : firstRun.c firstRun.h
	gcc -g -ansi -Wall -pedantic firstRun.c -o firstRun.o
secondRun.o : secondRun.c secondRun.h
	gcc -g -ansi -Wall -pedantic secondRun.c -o secondRun.o
fileOutput.o : fileOutput.c fileOutput.h
	gcc -g -ansi -Wall -pedantic fileOutput.c -o fileOutput.o
