
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macroManager.h"

static int macroCount = 0;
static char** macroNames;
static LineNode** macros;


void findMacros(LineNode* head);
void deleteLocalArrays();
char* getMacroCallName(char* lineContent);
int getMacroIndex(char* macroName);


bool macroManager(LineNode* head) { 

    findMacros(head);

    int currentIndex = 0;
    LineNode* currentLine = head;
    /* iterate on all lines to find macro calls*/
    while (NULL != currentLine) {
        char* macroCallName = getMacroCallName(currentLine->Content);
        /* if this line is NOT a macro call - move on*/
        if (NULL == macroCallName) {
            currentLine = currentLine -> Next;
            currentIndex++;
            continue;
        }
        
        int macroIndex = getMacroIndex(macroCallName);
        /* if the macro name is unrecognized*/
        if (-1 == macroIndex) {
            /* error: calling to an undefined macro*/
            return FALSE;
        }

        LineNode* copiedMacro = CopyLines(macros[macroIndex]);
        DeleteAt(head, currentIndex, 1); /* delete the macro call*/
        InsertLinesSection(head, copiedMacro, currentIndex);

        currentLine = currentLine -> Next;
        currentIndex++;
    }
    free(currentLine);
    deleteLocalArrays();
    return TRUE;
}


void findMacros(LineNode* head) {
    LineNode* current = head;
    LineNode* prev = head;
    char keyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    int line = 1, startLine, lineAmount;

    while (NULL != current) {
        getWord(current, 1, keyWord);
        if (0 == strcmp("macro", keyWord)) {
            macroCount++;
            startLine = line;
            getWord(current, 2, keyWord);
            DeleteAt(head, line, 1);
            line--;
            macroNames[macroCount-1] = keyWord;
        }
        if(0 == strcmp("endmacro", keyWord)) {
            DeleteAt(head, line, 1);
            line--;
            lineAmount = line - startLine;
            macros[macroCount-1] -> Content = ExtractLines(head, startLine, lineAmount);
            line = startLine;
        }
        line++;
    }
    free(current);
    free(prev);
    free(keyWord);
}

void deleteLocalArrays() {
    free(macroNames);
    free(macros);
    return;
}

char* getMacroCallName(char* lineContent) {
    int i;
    for (i = 0; i <= sizeof(macroNames); i++) {
        if (lineContent == macroNames[i]) {
            return macroNames[i];
        }
    }
    return NULL;
}

int getMacroIndex(char* macroName) {
    int i;
    for (i = 0; i <= sizeof(macroNames); i++) {
        if (macroName == macroNames[i]) {
            return i;
        }
    }
    return -1;
}
