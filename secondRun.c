
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "secondRun.h" 

void closeAllSystems(LineNode* head, LineNode* binHead);
bool addSymbolAsEntry(LineNode* head, LineNode* current);
int binaryCodingProcess(LineNode* head, LineNode* current, LineNode* currentBinary);

char getSymbolName(char* keyWord);
int getLabelType(char* keyWord);
int getLabelAddress(char* keyWord);

LineNode* createAllBinHeadNode();

void decimalToBinary(char* binNum, int num, int length);
void negIntToBin(char* binNum, int num, int length);
char BinCharToBase32(char* binaryNum);
char intToBase32(int decimalNum);
char getMarkFor32Base(int num);


bool is_success =true;

LineNode* secondRun(LineNode* head) {
    IC = 0; /* line 1*/
    int L;
    LineNode* binHead = createAllBinHeadNode();
    LineNode* current = head;
    LineNode* currentBinary = binHead;

    while (NULL != current) { /* line 2*/
        /* line 3*/
        if (0 != isDataStorage(current)) { /* line 3 + 4*/
            if (true == isEntryGuidance(current)) { /* line 5*/
                is_success = addSymbolAsEntry(head, current); /* line 6*/
            } else {
                L = binaryCodingProcess(head, current, currentBinary); /* line 7*/
            }
        } /* go to line 2*/
        
        IC += L; /* line 8*/
        L = 0; /* So that we won't load the poor IC twice by mistake*/
        current = current -> Next; /* line 9*/
        currentBinary = currentBinary -> Next; /* line 9*/
    }

    if (false == is_success) { /* line 10*/
        return NULL;
    }
    return binHead;
}

void closeAllSystems(LineNode* head, LineNode* binHead) {
    DeleteAllLines(head);
    DeleteAllLines(binHead);

    symbolEntryNode* currentSymbol = symbolTableHead;
    symbolEntryNode* NextSymbol = symbolTableHead;

    while (NULL != currentSymbol) {
        NextSymbol = currentSymbol -> Next;
        free(currentSymbol);
        currentSymbol = NextSymbol;
    }
    symbolTableHead = NULL;
}

bool addSymbolAsEntry(LineNode* head, LineNode* current) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    bool flag =false;
    getWord(current, 2, keyWord);
    
    flag = addToTable(head, current, 2);
    while ((NULL != currentSymbol -> Next)) {
        currentSymbol -> Type = entry;
        currentSymbol -> Address = 0;
    }

    free(keyWord);
    return flag;
}

int binaryCodingProcess(LineNode* head, LineNode* current, LineNode* currentBinary) {
    /* go line by line and fill the currentBin -> Content with strcat */
    int returnVal = 1;
    int wordLoc = 1;
    int foundRegister = 0;
    LineNode* operandCurrentBinary;
    int wordCount = 0;
    int tempOpCodeNum = getOpCodeInTable(head, current);
    if (true == isSymbol(current)) {
        wordLoc++;
    }
    if (0 != tempOpCodeNum) {
        /* enter opCode*/
        operandCurrentBinary = currentBinary -> Next;
        char* binNum = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
        decimalToBinary(binNum, getOpCodeInTable(head, current) - 1, OPCODE_BIT_SIZE); 
        strcat(currentBinary -> Content, binNum);
        free(binNum);
        wordLoc++;

        if (15 == tempOpCodeNum || 16 == tempOpCodeNum) { /* zero operand*/
            strcat(currentBinary -> Content, "0000");
            wordCount = 2;
        }
        if (5 <= tempOpCodeNum && 14 >= tempOpCodeNum && 7 != tempOpCodeNum) {/* one operand*/
            strcat(currentBinary -> Content, "00");
            wordCount = 1;
        }

        /*enter operands*/
        while (2 > wordCount) { /* scan each word in the line*/
            char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
            getWord(current, wordLoc, keyWord);
            
            if (0 != getRegister(keyWord)) { /* found a register*/
                strcat(currentBinary -> Content, "11");
                if (1 == wordCount) {
                    strcat(operandCurrentBinary -> Content, "0000");
                }
                char* binNum = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                decimalToBinary(binNum, getRegister(keyWord) - 1, OPCODE_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, binNum);
                free(binNum);
                if (1 == wordCount) {
                    strcat(operandCurrentBinary -> Content, "00");
                }
                foundRegister++;

            } else if(1 == foundRegister) {
                strcat(operandCurrentBinary -> Content, "000000");
            }

            if (2 == isRegisterOrSymbol(keyWord)) { /* found a symbol with a dot*/
                strcat(currentBinary -> Content, "10");
                char tempKeyWord;
                strcpy(tempKeyWord, keyWord);
                tempKeyWord = strtok(keyWord, ".");

                char* binNum1 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                decimalToBinary(binNum1, getLabelAddress(tempKeyWord), SYMBOL_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, binNum1);
                free(binNum1);
                strcat(operandCurrentBinary -> Content, "10");
                
                operandCurrentBinary = operandCurrentBinary -> Next;
                char* binNum2 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                decimalToBinary(binNum2, (int)binNum2[sizeof(binNum2) -1], SYMBOL_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, binNum2);
                free(binNum2);
                strcat(operandCurrentBinary -> Content, "00");
                returnVal++;
            }
            if (1 == getLabelType(keyWord) || 2 == getLabelType(keyWord) ) {  /* a pre-define label*/
                strcat(currentBinary -> Content, "01");
                if (1 == getLabelType(keyWord)) {
                    strcat(operandCurrentBinary -> Content, "0000000001");
                } else if (2 == getLabelType(keyWord)) {
                    char* binNum = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    decimalToBinary(binNum, getLabelAddress(keyWord), SYMBOL_BIT_SIZE);
                    strcat(operandCurrentBinary -> Content, binNum);
                    free(binNum);
                    strcat(operandCurrentBinary -> Content, "10");
                }
                getLabelAddress(keyWord);
            }
            if (0 == strcmp(keyWord[0], "#") ) { /* the request is local*/
                char tempKeyWord;
                strcat(currentBinary -> Content, "00");
                tempKeyWord = strtok(keyWord, "#");
                char* tempNumWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                negIntToBin(tempNumWord, (int)tempKeyWord, DATA_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, tempNumWord);
                strcat(operandCurrentBinary -> Content, "00");
            }

            if (0 == wordCount && 0 == foundRegister) {
                operandCurrentBinary = operandCurrentBinary -> Next;
            }

            free(keyWord);
            returnVal++;
            wordLoc++;
            wordCount++;
        }
    } else {
        returnVal = 0;
        bool negFlag =false, commaFlag =false;
        int i, j;
        
        char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
        getLineFromPoint(current, ++wordLoc, keyWord);

        for (i = 0; i < sizeof(keyWord); i++) {
            if (0 != strcmp(keyWord[i], ",")) {
                char tempChar = keyWord[i];
                if (0 == strcmp(keyWord[i], '-')) {
                    tempChar = keyWord[++i];
                    negFlag =true;
                }
                if (0 == strcmp(keyWord[i], '"')) {
                    commaFlag =true;
                    j = i + 1;
                }
                while (0 != strcmp(keyWord[i+1], ",") || sizeof(keyWord)-1 == i) {
                    strcat(tempChar, keyWord[++i]);
                }

                if (10 > (int)keyWord[i]) { /* found a number*/
                    char* tempKeyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    decimalToBinary(tempKeyWord, (int)tempChar, DATA_BIT_SIZE);
                    strcat(operandCurrentBinary -> Content, tempKeyWord);
                    free(tempKeyWord);
                }
                if (true == negFlag) { /* found a negative number*/
                    tempChar = strtok(tempChar, "-");
                    char* tempKeyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    negIntToBin(tempKeyWord, (int)tempChar, DATA_BIT_SIZE);
                    strcat(operandCurrentBinary -> Content, tempKeyWord);
                    free(tempKeyWord);
                }
                if (true == commaFlag) { /* found a string*/
                    while (0 != strcmp(keyWord[i], '"')) {
                        char* tempKeyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                        negIntToBin(tempKeyWord, (int)keyWord[j], DATA_BIT_SIZE);
                        strcat(operandCurrentBinary -> Content, tempKeyWord);
                        free(tempKeyWord);
                        returnVal++;
                        j++;
                    }
                    strcat(operandCurrentBinary -> Content, "0000000000");
                }
            }
            returnVal++;
        }
    }
    return returnVal;
}

char getSymbolName(char* keyWord) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    while (NULL != currentSymbol) {
        if (0 == strcmp(currentSymbol -> Content, keyWord)) {
            return currentSymbol -> Name;
        }
    }
    return NULL;      
}

int getLabelType(char* keyWord) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    while (NULL != currentSymbol) {
        if (0 == strcmp(currentSymbol -> Content, keyWord)) {
            return currentSymbol -> Type;
        }
    }
    return -1;       
}

int getLabelAddress(char* keyWord) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    while (NULL != currentSymbol) {
        if (0 == strcmp(currentSymbol -> Content, keyWord)) {
            return currentSymbol -> Address;
        }
    }
    return -1;       
}

LineNode* createAllBinHeadNode() { /* edit at home*/
    LineNode* binHead = (LineNode*)malloc(sizeof(LineNode));
    int i;
    for (i = 0; i <= DC; i++) {
        addNewNode(binHead, NULL);
    }
    return binHead;
}

void decimalToBinary(char* binNum, int num, int length) {
    int counter = 0;
    unsigned leftoverNum;
    for (leftoverNum = (1 << length - 1); leftoverNum > 0; leftoverNum = leftoverNum / 2) {
        binNum[counter++] = (num & leftoverNum) ? '1' : '0';
    }
    binNum[counter] = '\0';
    return;
}

void negIntToBin(char* binNum, int num, int length) {
    num--;
    int counter = 0;
    unsigned leftoverNum;
    for (leftoverNum = (1 << length - 1); leftoverNum > 0; leftoverNum = leftoverNum / 2) {
        binNum[counter++] = (num & leftoverNum) ? '0' : '1';
    }
    binNum[counter] = '\0';
    return;
}

char BinCharToBase32(char* binaryNum) {
    int i, j = 1, decimalNum = 0;
    int leftNum, rightNum;
    char returnVal;
    for(i = sizeof(binaryNum) -1; i >= 0; i--) {
        if (strcmp(binaryNum[i], "1")) {
            decimalNum += j;
        }
        j *= 2;
    }
    returnVal = intToBase32 (decimalNum);
    return returnVal;
    /*leftNum = decimalNum >> 5;
    rightNum = decimalNum - leftNum << 5;

    char leftCh = getMarkFor32Base(leftNum);
    char rightCh = getMarkFor32Base(rightNum);
    strcat(leftCh, rightCh);

    return leftCh;*/
}

char intToBase32(int decimalNum) {
    if (32 > decimalNum) {
        return getMarkFor32Base(decimalNum);
    }
    char leftCh = getMarkFor32Base(decimalNum/32);
    char rightCh = getMarkFor32Base(decimalNum%32);
    strcat(leftCh, rightCh);
    return leftCh;
}

char getMarkFor32Base(int index) {
    return "!@#$%^&*<>abcdefghijklmnopqrstuv"[index];
}