#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macroManager.h"
#include "firstRun.h"

bool is_success = TRUE; /*error tracker*/

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
    is_success = firstRun(head);
    if (TRUE == is_success) {
        LineNode* binHead;
	    binHead = secondRun(head);

	    return binHead;    
    }
	return NULL;
}
