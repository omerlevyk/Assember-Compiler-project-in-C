CREATOR = -ansi -Wall -pedantic
OBJS = main.o LinesManager.o macroManager.o firstRun.o secondRun.o filesOutput.o

main : $(OBJS)
	gcc -g -c $(CREATOR) $(OBJS) -o main
main.o : main.c globalFun.h LinesManager.h macroManager.h firstRun.h secondRun.h filesOutput.h
	gcc -g -c $(CREATOR) main.c -o main.o
LinesManager.o : LinesManager.c LinesManager.h
	gcc -g -c $(CREATOR) LinesManager.c -o LinesManager.o
macroManager.o : macroManager.c macroManager.h
	gcc -g -c $(CREATOR) macroManager.c -o macroManager.o
firstRun.o : firstRun.c firstRun.h
	gcc -g -c $(CREATOR) firstRun.c -o firstRun.o
secondRun.o : secondRun.c secondRun.h
	gcc -g -c $(CREATOR) secondRun.c -o secondRun.o
filesOutput.o : filesOutput.c filesOutput.h
	gcc -g -c $(CREATOR) filesOutput.c -o filesOutput.o
