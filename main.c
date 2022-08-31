#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globalFun.h"
#include "LinesManager.h"
#include "macroManager.h"
#include "firstRun.h"
#include "secondRun.h"
#include "filesOutput.h"

#include "LinesManager.c"
#include "macroManager.c"
#include "firstRun.c"
#include "secondRun.c"
#include "filesOutput.c"


LineNode* compilerRun(LineNode* head);


int main(int argc, const char* argv[]) {   
    LineNode* head = NULL;
    LineNode* binHead;

    head = LoadFile(argv[1]);
    macroManager(head);
    binHead = compilerRun(head);
    writeToFiles(argv[1], head, binHead);

    closeAllSystems(head, binHead);
    return 0;
}

LineNode* compilerRun(LineNode* head) {
    bool is_success = firstRun(head);
    if (true == is_success) {
        LineNode* binHead;
	    binHead = secondRun(head);

	    return binHead;    
    }
	return NULL;
}
