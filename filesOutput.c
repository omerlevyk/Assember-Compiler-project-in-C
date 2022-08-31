#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesOutput.h"

void writeBinHeadToFile (char* fileName, LineNode* binHead, symbolEntryNode* symbolTableHead);
void writeToFileAfterMacros(LineNode* head, char* path);
void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);
void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);

/* void writeList(outputPath, listHead, convertingFunction=NULL)*/



void writeToFiles(char* fileName, LineNode* head, LineNode* binHead) {
    /* writeToFileAfterMacros(head, fileName);*/ /* after macro stage file - for testing*/
    if (NULL != binHead) { /* encoding file*/
        symbolEntryNode* currentSymbol = symbolTableHead;
        bool externExist =false, entryExist =false;
        while (NULL != currentSymbol) {
            if (external == currentSymbol -> Type) {
                externExist =true;
            } else if (entry == currentSymbol -> Type) { /* entry file*/
                entryExist =true;
            }
        }
        if (true == externExist) {
            writeExternToFile(head, symbolTableHead, fileName);
        }
        if (true == entryExist) {
            writeEntryToFile(head, symbolTableHead, fileName);
        }
        writeBinHeadToFile(fileName, symbolTableHead, binHead);
    }
    return;
}

void writeBinHeadToFile(char* fileName, LineNode* binHead, symbolEntryNode* symbolTableHead) {
    FILE * fptr;
    LineNode* currentBin = binHead;
    int lineIndex = IC_VALUE; /* IC_VALUE == 100*/
    strcat(fileName, ".ob");
    fptr = fopen(fileName, "w");

    while (NULL != currentBin) {
        fprintf(fptr, "%s" , intToBase32(lineIndex));
        fprintf(fptr,"\t");
        fprintf(fptr, "%s" , BinCharToBase32(currentBin -> Content));
        fprintf(fptr,"\n");
        currentBin = currentBin -> Next;
        lineIndex++;
    }
    free(fptr);
    free(fileName);
}

void writeToFileAfterMacros(LineNode* head, char* fileName) {
    FILE * fptr;
    strcat(fileName, ".as");
    fptr = fopen(fileName, "w");
    LineNode* current = head;

    if(NULL == fptr) {
        getErrorDescription(head, head, fileName, 1);
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

void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* fileName){
    FILE * fptr;
    strcat(fileName, ".ext");
    fptr = fopen(fileName, "w");
    symbolEntryNode* currentSymbol = symbolTableHead;
    
    if(NULL == fptr) {
        getErrorDescription(head, head, fileName, 1);
    } else {
        while(currentSymbol != NULL) {
            if (external == currentSymbol -> Type) {
                fprintf(fptr, "%s\t%s" , currentSymbol -> Name, intToBase32(currentSymbol -> Address));
                fprintf(fptr,"\n");
            }
            currentSymbol = currentSymbol -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}

void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* fileName) {
    FILE * fptr;
    strcat(fileName, ".ent");
    fptr = fopen(fileName, "w");
    symbolEntryNode* currentSymbol = symbolTableHead;
    
    if(NULL == fptr) {
        getErrorDescription(head, head, fileName, 1);
    } else {
        while(currentSymbol != NULL) {
            if (entry == currentSymbol -> Type) {
                fprintf(fptr, "%s\t%s" , currentSymbol -> Name, intToBase32(currentSymbol -> Address));
                fprintf(fptr,"\n");
            }
            currentSymbol = currentSymbol -> Next;
        }
    }
    fclose(fptr);
    free(fileName);
}
