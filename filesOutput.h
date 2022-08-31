#ifndef FILES OUTPUT.H
#define FILES OUTPUT.H

#include "secondRun.h"


/* write to Files*/
void writeBinHeadToFile (char* fileName, LineNode* binHead, symbolEntryNode* symbolTableHead);
void writeToFileAfterMacros(LineNode* head, char* path);
void writeExternToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);
void writeEntryToFile(LineNode* head, symbolEntryNode* symbolTableHead, char* path);

#endif