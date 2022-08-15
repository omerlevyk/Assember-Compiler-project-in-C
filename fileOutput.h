#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondRun.h"


/* write to Files*/
void writeBinHeadToFile (LineNode* head, symbolEntryNode* symbolTableHead, LineNode* binHead, char* path);
void writeToFileAfterMacros(LineNode* head, char* path);
void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);
void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);
