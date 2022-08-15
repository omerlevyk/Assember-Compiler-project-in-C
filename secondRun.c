
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondRun.h" 


bool addSymbolAsEntry(LineNode* head, LineNode* current);
int binaryCodingProcess(LineNode* head, LineNode* current, LineNode* currentBinary);

char getSymbolName(char* keyWord);
int getLabelType(char* keyWord);
int getLabelAddress(char* keyWord);

LineNode* createAllBinHeadNode();

void decimalToBinary(char* binNum, int num, int length);
void negIntToBin(char* binNum, int num, int length);
char convertToBase32(int num);
char getMarkFor32Base(int num);


bool is_success =TRUE;

LineNode* secondRun(LineNode* head) {
    IC = 0; /* line 1*/
    int L;
    LineNode* binHead = createAllBinHeadNode();
    LineNode* current = head;
    LineNode* currentBinary = binHead;

    while (NULL != current) { /* line 2*/
        /* line 3*/
        if (0 != isDataStorage(current)) { /* line 3 + 4*/
            if (TRUE == isEntryGuidance(current)) { /* line 5*/
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

    if (FALSE == is_success) { /* line 10*/
        return NULL;
    }
}

bool addSymbolAsEntry(LineNode* head, LineNode* current) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    char keyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    bool flag =FALSE;
    getWord(current, 2, keyWord);
    
    flag = addToTable(head, current, 2);
    while ((NULL != currentSymbol -> Next)) {
        currentSymbol -> Type = entry;
        currentSymbol -> Address = 0; //??
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
    if (TRUE == isSymbol(current)) {
        wordLoc++;
    }
    if (0 != tempOpCodeNum) {
        /* enter opCode*/
        operandCurrentBinary = currentBinary -> Next;
        char* binNum[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
        decimalToBinary(binNum, getOpCodeInTable(head, current) - 1, OPCODE_BIT_SIZE); 
        strcat(currentBinary -> Content, binNum);
        free(binNum);
        wordLoc++;

        if (15 == tempOpCodeNum || 16 == tempOpCodeNum) { //zero operand
            strcat(currentBinary -> Content, "0000");
            wordCount = 2;
        }
        if (5 <= tempOpCodeNum && 14 >= tempOpCodeNum && 7 != tempOpCodeNum) {//one operand
            strcat(currentBinary -> Content, "00");
            wordCount = 1;
        }

        /*enter operands*/
        while (2 > wordCount) { /* scan each word in the line*/
            char* keyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
            getWord(current, wordLoc, keyWord);
            
            if (0 != getRegister(keyWord)) { /* found a register*/
                strcat(currentBinary -> Content, "11");
                if (1 == wordCount) {
                    strcat(operandCurrentBinary -> Content, "0000");
                }
                char* binNum[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
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

            if (2 == isRegisterOrSymbol(keyWord)) { // found a symbol with a dot
                strcat(currentBinary -> Content, "10");
                char tempKeyWord;
                strcpy(tempKeyWord, keyWord);
                tempKeyWord = strtok(keyWord, ".");

                char* binNum[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                decimalToBinary(binNum, getSymbolAddress(tempKeyWord), SYMBOL_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, binNum);
                free(binNum);
                strcat(operandCurrentBinary -> Content, "10");
                
                operandCurrentBinary = operandCurrentBinary -> Next;
                char* binNum[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                decimalToBinary(binNum, (int)binNum[sizeof(binNum) -1], SYMBOL_BIT_SIZE);
                strcat(operandCurrentBinary -> Content, binNum);
                free(binNum);
                strcat(operandCurrentBinary -> Content, "00");
                returnVal++;
            }
            if (1 == getLabelType(keyWord) || 2 == getLabelType(keyWord) ) {  /* a pre-define label*/
                strcat(currentBinary -> Content, "01");
                if (1 == getLabelType(keyWord)) {
                    strcat(operandCurrentBinary -> Content, "0000000001");
                } else if (2 == getLabelType(keyWord)) {
                    char* binNum[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    decimalToBinary(binNum, getSymbolAddress(keyWord), SYMBOL_BIT_SIZE);
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
                char* tempNumWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
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
        bool negFlag =FALSE, commaFlag =FALSE;
        int i, j;
        
        char* keyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
        getLineFromPoint(current, ++wordLoc, keyWord);

        for (i = 0; i < sizeof(keyWord); i++) {
            if (0 != strcmp(keyWord[i], ",")) {
                char tempChar = keyWord[i];
                if (0 == strcmp(keyWord[i], '-')) {
                    tempChar = keyWord[++i];
                    negFlag =TRUE;
                }
                if (0 == strcmp(keyWord[i], '"')) {
                    commaFlag =TRUE;
                    j = i + 1;
                }
                while (0 != strcmp(keyWord[i+1], ",") || sizeof(keyWord)-1 == i) {
                    strcat(tempChar, keyWord[++i]);
                }

                if (10 > (int)keyWord[i]) { /* found a number*/
                    char* tempKeyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    decimalToBinary(tempKeyWord, (int)tempChar, DATA_BIT_SIZE);
                    strcat(operandCurrentBinary -> Content, tempKeyWord);
                    free(tempKeyWord);
                }
                if (TRUE == negFlag) { /* found a negative number*/
                    tempChar = strtok(tempChar, "-");
                    char* tempKeyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
                    negIntToBin(tempKeyWord, (int)tempChar, DATA_BIT_SIZE);
                    strcat(operandCurrentBinary -> Content, tempKeyWord);
                    free(tempKeyWord);
                }
                if (TRUE == commaFlag) { /* found a string*/
                    while (0 != strcmp(keyWord[i], '"')) {
                        char* tempKeyWord[] = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
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

LineNode* createAllBinHeadNode() { //??
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

char convertToBase32(int num) {
    int firstLoc, secondLoc;
    char firstCh, secondCh;
    if (31 >= num) {
        firstLoc = 0;
        secondLoc = num;
    }
    while (32 <= secondLoc) {
        secondLoc = num/32;
        firstLoc++;
    }
    
    firstCh = convertToBase32(firstLoc);
    secondCh = convertToBase32(secondLoc);
    strcat(firstCh, secondCh);

    return firstCh;
}

char getMarkFor32Base(int num) {
    switch (num) {
        case 0:
            return "!";
            break;
        case 1:
            return "@";
            break;
        case 2:
            return "#";
            break;
        case 3:
            return "$";
            break;
        case 4:
            return "%";
            break;
        case 5:
            return "^";
            break;
        case 6:
            return "&";
            break;
        case 7:
            return "*";
            break;
        case 8:
            return "<";
            break;
        case 9:
            return ">";
            break;
        case 10:
            return "a";
            break;
        case 11:
            return "b";
            break;
        case 12:
            return "c";
            break;
        case 13:
            return "d";
            break;
        case 14:
            return "e";
            break;
        case 15:
            return "f";
            break;
        case 16:
            return "g";
            break;
        case 17:
            return "h";
            break;
        case 18:
            return "i";
            break;
        case 19:
            return "j";
            break;
        case 20:
            return "k";
            break;
        case 21:
            return "l";
            break;
        case 22:
            return "m";
            break;
        case 23:
            return "n";
            break;
        case 24:
            return "o";
            break;
        case 25:
            return "p";
            break;
        case 26:
            return "q";
            break;
        case 27:
            return "r";
            break;
        case 28:
            return "s";
            break;    
        case 29:
            return "t";
            break;
        case 30:
            return "u";
            break;
        case 31:
            return "v";
            break;
    }
}