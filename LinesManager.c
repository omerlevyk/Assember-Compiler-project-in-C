#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinesManager.h"

LineNode* LoadFile(char* path);
LineNode* CopyLines(LineNode* head);
void addNewNode(LineNode* head, char* contentForNewNode);
void DeleteAllLines(LineNode* head);
int GetFileLength(LineNode* head);
int getLineNumber(LineNode* head, LineNode* nodeLoc);
LineNode* ExtractLines(LineNode* head, int fromLine, int length);
void DeleteAt(LineNode* head, int index, int linesAmount);
LineNode* InsertLinesSection(LineNode* head, LineNode* section, int insertAt);
bool getWord(LineNode* current, int wordLoc, char* ch);
bool getLineFromPoint(LineNode* current, int wordLoc, char* strLine);
void getErrorDescription(LineNode* head, LineNode* current, char* ch, int errNum);


LineNode* LoadFile(char* path) {
    FILE *fp;
    char* fpFileName;
    char line[MAX_LINE_LENGTH];
    LineNode* current, * head;

    head = current = NULL;
    fpFileName = strcat(path, ".as");
    fp = fopen(fpFileName, "r");
    if (NULL == fp) {
        getErrorDescription(head, current, fpFileName, 1);
    }

    while(fgets(line, sizeof(line), fp)){
        LineNode* current = malloc(sizeof(LineNode));
        current-> Content = strdup(line);
        current-> Next = NULL;

        if(head == NULL) {
            current = head;
        } else {
            current = current-> Next;
        }
    }
    fclose(fp);
    return head;
}

LineNode* CopyLines(LineNode* head) {
    LineNode* current = head;
    LineNode* section = head;
    while (NULL != current) {
        section = current;
        current = current -> Next;
    }
    return section;
}

void addNewNode(LineNode* head, char* contentForNewNode) {
    LineNode* current = head;
    while (NULL != current -> Next) {
        current = current -> Next;
    }
    LineNode* newNode = (struct LineNode*) malloc(sizeof(LineNode));
    current -> Next = newNode;
    current = current -> Next;
    current -> Content = contentForNewNode;
    
}

void DeleteAllLines(LineNode* head) {
    LineNode* current = head;
    LineNode* Next;

    while(NULL != current) {
        Next = current -> Next;
        free(current);
        current = Next;
    }
    head = NULL;
}

int GetFileLength(LineNode* head) {
    LineNode* current = head;
    int lineNumCounter = 0;
    while (NULL != current)
    {
        lineNumCounter++;
        current = current -> Next;
    }
    return lineNumCounter;
}

int getLineNumber(LineNode* head, LineNode* nodeLoc) {
    int lineNumCounter = 1;
    LineNode* current = head;
    while (NULL != current) {
        if (strcmp(current-> Content, nodeLoc -> Content)) {
            return lineNumCounter;
        }
        lineNumCounter++;
    }
    return -1;
}

LineNode* ExtractLines(LineNode* head, int fromLine, int length) {
    LineNode* section;
    LineNode* current = head;
    LineNode* prev = head;
    int i;
    for(i = 0; NULL != current; i++) {
        if (fromLine > i) {
            prev = current;
            current = current -> Next;
        }
        if (fromLine == i) {
            section = current;
            current = current -> Next;   
        }
        if (fromLine + length >= i && fromLine < i) {
            current = current -> Next;
            section -> Next = current;
        }
        if (fromLine + length == i+1) {
            prev -> Next = current;
            current = current -> Next;
        } else {
            current = current -> Next;
        }
    }
    return section;
}

void DeleteAt(LineNode* head, int index, int linesAmount) {
    LineNode* current = head;
    LineNode* prev = head;
    int i;
    for(i = 0; NULL != current; i++) {
        if (i + 1 == index) {
            prev = current;
        }
        if (i + 1 == index+linesAmount) {
            prev -> Next = current;
        }
        current = current -> Next;
    }
}

LineNode* InsertLinesSection(LineNode* head, LineNode* section, int insertAt) {
    LineNode* current = head;
    LineNode* prev = head;
    int i;
    for(i = 0; NULL != current; i++) {
        if (insertAt == i) {
            prev -> Next = section;
            section -> Next = current;
        }

        current = current -> Next;
    }
    return head;
}

bool getWord(LineNode* current, int wordLoc, char* ch) {
    int i = 1;
    char strLine;
    strcpy(strLine, current -> Content);
    for (i = 1; NULL != strLine; i++) {
        ch = strtok(strLine, ",");
        ch = strtok(strLine, " ");
        if (i == wordLoc) {
            return true;
        }
    }
    ch = NULL;
    return false;    
}

bool getLineFromPoint(LineNode* current, int wordLoc, char* strLine) {
    int i = 0;
    char ch;
    strcpy(strLine, current -> Content);
    for (i = 1; NULL != strLine; i++) {
        ch = strtok(strLine, " ");
        if (i == wordLoc) {
            return true;
        }
    }
    return false;    
}

void getErrorDescription(LineNode* head, LineNode* current, char* ch, int errNum) {
    switch (errNum) {
    case 1:
        /*Can't open file/ file does not exist */
        fprintf(stdout, "Error: file '%s.as' can't be read", ch);
        break;
    case 2:
        /* The symbol exists more than once */
        fprintf(stdout, "The symbol '%s' at line %d exists more than once", ch, getLineNumber(head, current));
        break;
    case 3:
        /* The action does not exist*/
        fprintf(stdout, "The action  in line %d does not exist", getLineNumber(head, current));
        break;
    case 4:
        /* The number of operands is incorrect */
        fprintf(stdout, "The number of operands in line %d is incorrect", getLineNumber(head, current));
        break;
    case 5:
        /* invalided operation type*/
        fprintf(stdout, "The operation type '%s' at line %d is invalided", ch , getLineNumber(head, current));
        break;
    case 6:
        /* The name of the register does not exist */
        fprintf(stdout, "The name of the register '%s' at line %d does not exist", ch , getLineNumber(head, current));
        break;
    case 7:
        /* Invalid addressing method number for the source operand */
        fprintf(stdout, "Invalid addressing method number for the source operand at line '%d'", getLineNumber(head, current));
        break;
    case 8:
        /* The number of addressing methods is invalid for the destination operand */
        fprintf(stdout, "The number of addressing methods at line %d is invalid for the destination operand", getLineNumber(head, current));
        break;
    case 9:
        /* invalided operand*/
        fprintf(stdout, "invalided operand '%s' at line %d", ch , getLineNumber(head, current));
        break;
    default:
        /* Can't find a error*/
        fprintf(stdout, "Something went wrong, can't find a error");
        break;
    }
}
