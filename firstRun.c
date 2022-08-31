
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "firstRun.h"


bool isSymbol(LineNode* current);
bool checkAfterStruct (LineNode* head, LineNode* current);
int getRegister (char* keyWord);
int isRegisterOrSymbol(char* keyWord);

int isDataStorage(LineNode* current);
void addToMemory(LineNode* head, LineNode* current, int dataTypeNum);
bool isEntryGuidance(LineNode* current);
bool isExternGuidance(LineNode* current);

bool checkLabel(symbolEntryNode* symbolHead, char* symbol);
bool addToTable(LineNode* head, LineNode* current, int wordLoc);
void addExternalSymbol(LineNode* head, LineNode* current);

int getDCval(LineNode* head, LineNode* current, char* keyWord, int dataTypeNum);
int countCharForDC(char* keyWord, int i);
int countIntegersForDC(char* keyWord, int i);
void IC_update(symbolEntryNode* symbolTableHead);

int getOpCodeInTable(LineNode* head, LineNode* current);
int opStructureAnalysis(LineNode* head, LineNode* current);
int two_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1, char* keyWord2);
int one_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1);
int zero_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum);


bool firstRun(LineNode* head) {
    /* line 1:*/
    LineNode* current = head;
    bool is_success = true;
    while(NULL != current) { /* line 2*/
        bool symbolFlag = isSymbol(current); /* line 3 + 4*/

        if(0 != isDataStorage(current)) { /* line 5*/
            if (true == symbolFlag) { /* line 6*/
                if (3 == isDataStorage(current)) {
                    is_success = checkAfterStruct(head, current);
                }
                addToTable(head, current, 1);
                symbolEntryNode* currentSymbol = symbolTableHead;
                while ((NULL != currentSymbol -> Next)) {
                    currentSymbol -> Type = data;
                    currentSymbol -> Address = DC;
                }
            }
            addToMemory(head, current, isDataStorage(current)); /* line 7*/
        } /* line 7*/
        else if(true == isEntryGuidance(current)) { /* line 8*/
            /* skip it*/
        }
        else if (true == isExternGuidance(current)) {/* line 9*/
            addExternalSymbol(head, current);
            
        }/* line 10*/
        else {
            if (true == symbolFlag) { /* line 11*/
                addToTable(head, current, 1);
            }
            if (0 == getOpCodeInTable(head, current)) { /* line 12*/
                is_success  =false;    
            }
            IC += opStructureAnalysis(head, current); /* line 13 + 14*/
        }
        current = current -> Next;
    }/* line 15*/
    if (true == is_success) { /* line 16*/
        IC_update(symbolTableHead); /* line 17*/
    }
    return is_success;
}

bool isSymbol(LineNode* current) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    getWord(current, 1, keyWord);
    if (strcmp(":", keyWord[strlen(keyWord) - 1])) {
        return true;
    } else {
        return false;
    }
}

bool checkAfterStruct (LineNode* head, LineNode* current) {
    bool returnVal = false;
    char* keyWord1 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    char* keyWord2 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    getWord(current, 3, keyWord1);
    getWord(current, 4, keyWord2);
    if ((int)keyWord1[0] < 10) {
        if (0 == strcmp(keyWord2[0], '"') && 0 == strcmp(keyWord2[sizeof(keyWord2)], '"')) {
            returnVal = true;
        }
    }
    free(keyWord1);
    free(keyWord2);
    return returnVal;
}

int getRegister (char* keyWord) {
    if (strcmp(keyWord, "r0")) {
        return r0;
    } else if (strcmp(keyWord, "r1")) {
        return r1;
    } else if (strcmp(keyWord, "r2")) {
        return r2;
    } else if (strcmp(keyWord, "r3")) {
        return r3;
    } else if (strcmp(keyWord, "r4")) {
        return r4;
    } else if (strcmp(keyWord, "r5")) {
        return r5;
    } else if (strcmp(keyWord, "r6")) {
        return r6;
    } else if (strcmp(keyWord, "r7")) {
        return r7;
    } else {
        return 0;
    }
}

int isRegisterOrSymbol(char* keyWord) {
    if (0 == getRegister(keyWord) ||true == isSymbol(keyWord)) {
        return 1;
    }
    char ch;
    strcpy(ch, keyWord);
    ch = strtok(ch, ".");
    if (0 != strcmp(keyWord, ch)) {
        if (true == isSymbol(ch)) {
            return 2;
        }
    }
    return 0;
}

int isDataStorage(LineNode* current) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    int returnVal = 0; /*false is the default*/
    int wordLoc = 1;

    if (true == isSymbol(current)) {
        wordLoc = 2;
    }
    if (true == getWord(current, wordLoc, keyWord)) {
        if (strcmp(".data", keyWord)) {
            returnVal = 1;
        }
        if (strcmp(".string", keyWord)) {
            returnVal = 2;
        }
        if (strcmp(".struct", keyWord)) {
            returnVal = 3;
        }
    }
    free(keyWord);
    return returnVal;
}

void addToMemory(LineNode* head, LineNode* current, int dataTypeNum) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    symbolEntryNode* currentSymbol = symbolTableHead;
    int wordLoc = 3;
    while ((NULL != currentSymbol -> Next)) {
        currentSymbol = currentSymbol -> Next;
    }
    getLineFromPoint(current, wordLoc, keyWord);
    currentSymbol -> Content = keyWord;
    DC += getDCval(head, current, keyWord, dataTypeNum);

    free(keyWord);
}

bool isEntryGuidance(LineNode* current) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    bool returnVal =false; /*false is the default*/
    if (true == getWord(current, 1, keyWord)) {
        if (strcmp(".entry", keyWord)) {
                returnVal =true;
        }
    }
    free(keyWord);
    return returnVal;
}

bool isExternGuidance(LineNode* current) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    bool returnVal =false; /*false is the default*/
    if (true == getWord(current, 1, keyWord)) {
        if (strcmp(".extern", keyWord)) {
                returnVal =true;
        }
    }
    free(keyWord);
    return returnVal;
}

bool checkLabel(symbolEntryNode* symbolHead, char* symbol) {
    if (NULL == symbolHead -> Name) {
        return true;
    }
    symbolEntryNode* currentSymbol = symbolHead; 
    while (NULL != currentSymbol) {
        if (0 != strcmp(symbol, currentSymbol -> Name)) {
            return false;
        }
    }
    return true;   
}

bool addToTable(LineNode* head, LineNode* current, int wordLoc) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    int duplicateVal =true;
    bool flag =false;
    /* get Name*/
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    getWord(current, wordLoc, keyWord);
    if (0 == strcmp(keyWord[strlen(keyWord) -1], ":")) { /* remove the ":" if there is one*/
        keyWord[strlen(keyWord) -1] = '\0';
    }
    
    if (!symbolTableHead) { /* if table is empty*/
        symbolTableHead = (symbolEntryNode*)malloc(sizeof(symbolEntryNode)); /* create a new table*/
        flag =true;
    } else {
        while (NULL != currentSymbol -> Next) {
            if(false == checkLabel(currentSymbol, keyWord)) {
                duplicateVal++;
            }
            currentSymbol = currentSymbol -> Next;
        }

        if (0 == duplicateVal) {
            symbolEntryNode* newSymbol = (symbolEntryNode*)malloc(sizeof(symbolEntryNode));
            currentSymbol -> Next = newSymbol;
            currentSymbol = currentSymbol -> Next;
            flag =true;
        } else {
            flag =false;
            getErrorDescription(head, current, keyWord, 2);
        }
        
    }
    currentSymbol -> Name = keyWord;
    free(keyWord);
    return flag;
}

void addExternalSymbol(LineNode* head, LineNode* current) {
    addToTable(head, current, 2);
    symbolEntryNode* currentSymbol = symbolTableHead;
    while ((NULL != currentSymbol -> Next)) {
        currentSymbol -> Type = external;
        currentSymbol -> Address = 0;
    }
}

int getDCval(LineNode* head, LineNode* current, char* keyWord, int dataTypeNum) {
    int i = 0, addDCcounter = 0, errCount = 0;
    bool negFlag = true, commaFlag = true; /* we need to check if there is no -- or ,, esc.*/
    char cutFromKeyWord;
    switch (dataTypeNum) {
        case 1: /* .data*/
            addDCcounter = countIntegersForDC(keyWord, 0);
            break;    

        case 2: /* .string*/
            addDCcounter = countCharForDC(keyWord, 0);
            break;
        case 3: /* .struct*/
            
            while (NULL != cutFromKeyWord) {
                if (10 > (int) keyWord[i] || 0 == strcmp(keyWord[i], "-")) { /* found an integer*/
                    addDCcounter += countIntegersForDC(keyWord, 0);
                }
                if (0 == strcmp(keyWord[i], '"')) { /* found a string*/
                    addDCcounter += countCharForDC(keyWord, 0);
                }
                cutFromKeyWord = strtok(keyWord, ",");
            }
            break;
    }
    if (0 < errCount) { /* line isn't ok */
        addDCcounter = 0;
        getErrorDescription(head, current, keyWord, 5);
    }
    return addDCcounter;
}

int countCharForDC(char* keyWord, int i) {
    int addDCcounter = 0, errCount = 0;
    for (i = 0; i < strlen(keyWord)-1 || 0 != strcmp(keyWord, ","); i++) {
        if (0 == strcmp(keyWord[0], '"')) { /* found a string*/
            if (0 == strcmp(keyWord[strlen(keyWord)-1], '"')) {
                for (i = 1; i < strlen(keyWord) - 2; i++) {
                    if (97 <= (int) keyWord[i] || 122 >= (int) keyWord[i]) { /* found a letter*/
                        addDCcounter++;
                    } else {
                        errCount++;
                    }
                }
            } else {
                errCount++;
            }
        } else {
            errCount++;
        }
    }
    addDCcounter++; /* in a string we need an empty line*/
    if (0 != errCount) {
        addDCcounter = 0;
    }
    return addDCcounter;
}

int countIntegersForDC(char* keyWord, int i) {
    int addDCcounter = 0, errCount = 0;
    bool negFlag =true, commaFlag =true; /* we need to check if there is no -- or ,, esc.*/
    while (i < strlen(keyWord) || 0 != strcmp(keyWord[i], '"')) {
        if (10 > (int) keyWord[i]) { /* found an integer*/
            addDCcounter++;
        }
        if (0 == strcmp(keyWord[i], ",")) {
            if (0 == addDCcounter ||false == commaFlag ||false == negFlag) {
                errCount++;
            }
            commaFlag =false;
        }
        if (0 == strcmp(keyWord[i], "-")) {
            negFlag =false;
            commaFlag =true;
        }
        if (0 == strcmp(keyWord[i], " ")) {
            if (false == negFlag) {
                errCount++;
            }
            continue;
        }
        i++;
    }
    if (0 != errCount) {
        addDCcounter = 0;
    }
    return addDCcounter;
}

void IC_update(symbolEntryNode* symbolTableHead) {
    symbolEntryNode* currentSymbol = symbolTableHead;
    while (NULL != currentSymbol) {
        if (data == currentSymbol -> Type) {
            currentSymbol -> Address += IC;
        }
        currentSymbol = currentSymbol -> Next;
    }
}

int getOpCodeInTable(LineNode* head, LineNode* current) {
    char* keyWord = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    int wordLoc = 1;
    int returnVal = 0;
    if (true == isSymbol(current)) {
        wordLoc = 2;
    }
    getWord(current, wordLoc, keyWord);

    if (true == strcmp("mov", keyWord)) {
        returnVal = mov;
    } else if (true == strcmp("cmp", keyWord)) {
        returnVal = cmp;
    } else if (true == strcmp("add", keyWord)) {
        returnVal = add;
    } else if (true == strcmp("sub", keyWord)) {
        returnVal = sub;
    } else if (true == strcmp("not", keyWord)) {
        returnVal = nott;
    } else if (true == strcmp("clr", keyWord)) {
        returnVal = clr;
    } else if (true == strcmp("lea", keyWord)) {
        returnVal = lea;
    } else if (true == strcmp("inc", keyWord)) {
        returnVal = inc;
    } else if (true == strcmp("dec", keyWord)) {
        returnVal = dec;
    } else if (true == strcmp("jmp", keyWord)) {
        returnVal = jmp;
    } else if (true == strcmp("bne", keyWord)) {
        returnVal = bne;
    } else if (true == strcmp("get", keyWord)) {
        returnVal = get;
    } else if (true == strcmp("prn", keyWord)) {
        returnVal = prn;
    } else if (true == strcmp("jsr", keyWord)) {
        returnVal = jsr;
    } else if (true == strcmp("rts", keyWord)) {
        returnVal = rts;
    } else if (true == strcmp("hlt", keyWord)) {
        returnVal = hlt;
    } else { /* returnVal is still zero*/
        getErrorDescription(head, current, keyWord, 9);
    }
    
    free(keyWord);
    return returnVal;
}

int opStructureAnalysis(LineNode* head, LineNode* current) {
    int opCodeNum = getOpCodeInTable(head, current);
    int addICcounter = 0;
    bool errFlag =true;

    int wordLoc = 2;
    if (true == isSymbol(current)) {
        wordLoc = 3;
    }
    char* keyWord1 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    char* keyWord2 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    char* keyWord3 = (char*)malloc(sizeof(char)*MAX_SIZE_CHAR);
    getWord(current, wordLoc, keyWord1);
    getWord(current, wordLoc +1, keyWord2);
    getWord(current, wordLoc +2, keyWord3);
    
    /* two operands*/
    if ((1 <= opCodeNum && 4 >= opCodeNum) || 7 == opCodeNum) {
        if (NULL != keyWord3) {
            errFlag =false;
            getErrorDescription(head, current, keyWord3, 4);
        }
        addICcounter += two_Operation_Operands(head, current, opCodeNum, keyWord1, keyWord2);

    /* one operands*/
    } else if ((8 <= opCodeNum && 14 >= opCodeNum) || (5 <= opCodeNum && 6 >= opCodeNum)) {
        if (NULL != keyWord2 || NULL != keyWord3) {
            errFlag =false;
            getErrorDescription(head, current, keyWord3, 4);
        }
        addICcounter += one_Operation_Operands(head, current, opCodeNum, keyWord1);
    
    /* zero operands*/
    } else if (15 <= opCodeNum && 16 >= opCodeNum) {
        if (NULL != keyWord1 || NULL != keyWord2 || NULL != keyWord3) {
            errFlag =false;
            getErrorDescription(head, current, keyWord3, 4);
        }
        addICcounter += 1;

    } else { /* 0 == opCodeNum or else*/
        errFlag =false;
        getErrorDescription(head, current, keyWord3, 5);
    }
    
    if (errFlag =false) {
        addICcounter = 0;
    }
    return addICcounter;
}

int two_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1, char* keyWord2) {
    int returnVal = 0, firstOperand = 0, secondOperand = 0;
    if (mov == opCodeNum) {
        firstOperand = isRegisterOrSymbol(keyWord1);
        secondOperand = isRegisterOrSymbol(keyWord2);
        if (0 != secondOperand && 0 != firstOperand) {
            returnVal = firstOperand + secondOperand + 1;
        }
    } else if (cmp == opCodeNum) {
        firstOperand = isRegisterOrSymbol(keyWord1);
        secondOperand = isRegisterOrSymbol(keyWord2);
        if (0 != secondOperand && 0 != firstOperand) {
            returnVal = firstOperand + secondOperand + 1;
        }
    } else if (add == opCodeNum) {
        firstOperand = isRegisterOrSymbol(keyWord1);
        secondOperand = isRegisterOrSymbol(keyWord2);
        if (0 == strcmp(keyWord1[0], "#")) {
            firstOperand = 1;
        }
        if (0 == strcmp(keyWord2[0], "#")) {
            secondOperand = 1;
        }
        if (0 != secondOperand && 0 != firstOperand) {
            returnVal = firstOperand + secondOperand + 1;
        }
    } else if (sub == opCodeNum) {
        firstOperand = isRegisterOrSymbol(keyWord1);
        secondOperand = isRegisterOrSymbol(keyWord2);
        if (0 == strcmp(keyWord1[0], "#")) {
            firstOperand = 1;
        }
        if (0 == strcmp(keyWord2[0], "#")) {
            secondOperand = 1;
        }
        if (0 != secondOperand && 0 != firstOperand) {
            returnVal = firstOperand + secondOperand;
        }
    } else if (lea == opCodeNum) {
        if (false != isSymbol(keyWord1)) {
            firstOperand += 1;
        }    
        secondOperand = isRegisterOrSymbol(keyWord2);
        if (0 != secondOperand && 0 != firstOperand) {
            returnVal = firstOperand + secondOperand + 1;
        }        
    }

    if (0 == returnVal) {
        getErrorDescription(head, current, keyWord1, 6);
    }
    return returnVal;
}

int one_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1) {  
    int returnVal;
    if (nott==opCodeNum || clr==opCodeNum || inc==opCodeNum || dec==opCodeNum || get==opCodeNum) {
        if (0 == getRegister(keyWord1) &&false == isSymbol(keyWord1)) {
            getErrorDescription(head, current, keyWord1, 6);
            returnVal = 0;
        } else {
            returnVal = 2;
        }     
    } else if (nott==opCodeNum || clr==opCodeNum || inc==opCodeNum || dec==opCodeNum || get==opCodeNum) {
        if (false == isSymbol(keyWord1)) {
            getErrorDescription(head, current, keyWord1, 6);
            returnVal = 0;
        } else {
            returnVal = 2;
        }
    } else if (prn==opCodeNum) {
        if (0 == getRegister(keyWord1) &&false == isSymbol(keyWord1)) {
            if (0 != strcmp("#", keyWord1[0])) {
                getErrorDescription(head, current, keyWord1, 6);
                returnVal = 0;   
            }
        }
        returnVal = 2;
    } else {
        getErrorDescription(head, current, keyWord1, 0);
        returnVal = 0;
    }
    return returnVal;
}
