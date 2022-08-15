#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileOutput.h"

void writeBinHeadToFile (LineNode* head, symbolEntryNode* symbolTableHead, LineNode* binHead, char* path);
void writeToFileAfterMacros(LineNode* head, char* path);
void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);
void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);


void writeToFiles(char* fileName, LineNode* head, LineNode* binHead) {
    
    writeToFileAfterMacros(head, fileName); /*after macro stage file*/
    if (NULL != binHead) { /*encoding file*/
        symbolEntryNode* currentSymbol = symbolTableHead;
        bool externExist =FALSE, entryExist =FALSE;
        while (NULL != currentSymbol) {
            if (external == currentSymbol -> Type) {
                externExist =TRUE;
            } else if (entry == currentSymbol -> Type) { /*entry file*/
                entryExist =TRUE;
            }
        }
        if (true == externExist) {
            writeExternToFile(head, symbolTableHead, fileName);
        }
        if (true == entryExist) {
            writeEntryToFile(head, symbolTableHead, fileName);
        }
        writeBinHeadToFile(head, symbolTableHead, binHead, fileName);
    }
    return;
}


void writeBinHeadToFile (LineNode* head, symbolEntryNode* symbolTableHead, LineNode* binHead, char* path) {
    FILE * fptr;
    char* fileName = strcat(path, ".ob");
    fptr = fopen(fileName, "w");
    LineNode* currentBin = binHead;

    if(NULL == fptr) {
        getErroDescription(head, head, path, 1);
    } else {
        while(currentBin != NULL) {
            fprintf(fptr, "%s" , currentBin -> Content);
            fprintf(fptr,"\n");
            currentBin = currentBin -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}

void writeToFileAfterMacros(LineNode* head, char* path) {
    FILE * fptr;
    char* fileName = strcat(path, ".as");
    fptr = fopen(fileName, "w");
    LineNode* current = head;

    if(NULL == fptr) {
        getErroDescription(head, head, path, 1);
    } else {
        while(current != NULL) {
            fprintf(fptr, "%s" , current -> Content);
            fprintf(fptr,"\n");
            current = current -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}

void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path){
    FILE * fptr;
    char* fileName = strcat(path, ".ext");
    fptr = fopen(fileName, "w");
    symbolEntryNode* currentSymbol = symbolTableHead;
    
    if(NULL == fptr) {
        getErroDescription(head, head, path, 1);
    } else {
        while(currentSymbol != NULL) {
            if (external == currentSymbol -> Type) {
                fprintf(fptr, "%s\t%s" , currentSymbol -> Name, get32Base(currentSymbol -> Address));
                fprintf(fptr,"\n");
            }
            currentSymbol = currentSymbol -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}

void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path) {
    FILE * fptr;
    char* fileName = strcat(path, ".ent");
    fptr = fopen(fileName, "w");
    symbolEntryNode* currentSymbol = symbolTableHead;
    
    if(NULL == fptr) {
        getErroDescription(head, head, path, 1);
    } else {
        while(currentSymbol != NULL) {
            if (entry == currentSymbol -> Type) {
                fprintf(fptr, "%s\t%s" , currentSymbol -> Name, get32Base(currentSymbol -> Address));
                fprintf(fptr,"\n");
            }
            currentSymbol = currentSymbol -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}
