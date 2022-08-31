#ifndef SECOND RUN.H
#define SECOND RUN.H 

#include "firstRun.h" 

/**
 * @brief secondRun - the third and last stage. in this stage the program has the code almost mapped.
 *      after a short gap filling, the program can convert the code into a machine.
 * 
 * @param int L - holds the amount on witch we needs to add to IC, judged by the size of the operands.
 * @param current - the current node in the lines linked list.
 * 
 * @return LineNode* a head of a new linked list filled by a machine code, NULL of the program fails. 
 */
LineNode* secondRun(LineNode* head);

/**
 * @brief closeAllSystems - delete all left pointers at the end of the program.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * @param NextSymbol - the next node in the table linked list.
 */
void closeAllSystems(LineNode* head, LineNode* binHead);

/**
 * @brief addSymbolAsEntry - adds a new node to the symbol table and mark as '.Entry'.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * 
 * @param keyWord - the current word the function is checking. 
 * @return true if success.
 * @return false if failed.
 */
bool addSymbolAsEntry(LineNode* head, LineNode* current);

/**
 * @brief binaryCodingProcess - fill the currentBin and the operandCurrentBinary Content in parallel,
 *      while self checking the size needed to add to IC.
 * 
 * @param returnVal - holds the value the function needs to return.
 * @param wordLoc - keeps track of the location of the current keyWord.
 * @param keyWord - the current word the function is checking.
 * @param foundRegister - a bool for self checking if there is two registers in the same line.
 * @param currentBinary - holds the node that we insert the opCode to.
 * @param operandCurrentBinary - holds the node that we insert the operand code to.
 * @param wordCount - checks if we are on the first or second word (after the opCode).
 * @param tempOpCodeNum - temp int that saves the current enum opCode.
 *  
 * @return int L to be added to IC (per requested in the instructions).
 */
int binaryCodingProcess(LineNode* head, LineNode* current, LineNode* currentBinary);

/**
 * @brief getSymbolName - get the name of the symbol.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * 
 * @return char the symbol's name if found, else return NULL.
 */
char getSymbolName(char* keyWord);

/**
 * @brief getLabelType - get the type of the symbol.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * 
 * @return int the symbol's type if found, else return -1.
 */
int getLabelType(char* keyWord);

/**
 * @brief getLabelAddress - get the address of the symbol.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * 
 * @return int the symbol's address if found, else return -1.
 */
int getLabelAddress(char* keyWord);


/**
 * @brief createAllBinHeadNode - create a new linked list and all the node necessary.
 * 
 * @param binHead - the head node in the binary lines linked list.
 * 
 * @return  LineNode the head of the new linked list.
 */
LineNode* createAllBinHeadNode();

/**
 * @brief decimalToBinary - convert a decimal number to binary number
 * 
 * @param binNum - store the binary number.
 * @param num - the number givin in a decimal form.
 * @param length - the amount of bytes needed.
 * @param counter - the counter for the byte used.
 * @param leftoverNum - holds the leftovers from num after divided.
 */
void decimalToBinary(char* binNum, int num, int length);

/**
 * @brief negIntToBin - convert a negative decimal number to a binary number
 * 
 * @param binNum - store the binary number.
 * @param num - the number givin in a decimal form.
 * @param length - the amount of bytes needed.
 * @param counter - the counter for the byte used.
 * @param leftoverNum - holds the leftovers from num after divided.
 */
void negIntToBin(char* binNum, int num, int length);

/**
 * @brief convert a number from binChar to decimal and send it to intToBase32().
 * 
 * @return char the number as base 32.
 */
char BinCharToBase32(char* binaryNum);

/**
 * @brief convert a number from decimal base to base 32.
 * 
 * @param int firstLoc - holds the number in the first location.
 * @param int secondLoc - holds the number in the second location.
 * @param char firstCh - holds the sign in the first location.
 * @param char secondCh - holds the sign in the second location.
 * 
 * @return char the combination of 'firstCh' and 'secondCh', both in 'firstCh'
 */
char intToBase32(int decimalNum);

/**
 * @brief switch-case that get the sign For a givin int in 32 Base.
 * 
 * @param num a number in decimal base.
 * 
 * @return char representative  to num in base 32.
 */
char getMarkFor32Base(int num);

#endif