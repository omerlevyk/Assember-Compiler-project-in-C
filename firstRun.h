#ifndef FIRST RUN.H
#define FIRST RUN.H 

#include "LinesManager.h"


symbolEntryNode* symbolTableHead;
/* memory counters*/
long IC = 0;
long DC = 0;


/**
 * @brief firstRun - the second big stage after macroManager.
 *      in this stage the program is mapping the code in preparation by
 *      filling the symbol table to the second run and check for errors. 
 * 
 * @param current - the current node in the lines linked list.
 * @param is_success - holds the bool value for if errors are founds.
 * 
 * @return true if no errors are found and the program can continue to the next stage.
 * @return false if errors are found and the program needs to stop.
 */
bool firstRun(LineNode* head);

/**
 * @brief isSymbol - checks if there is a symbol in this line.
 * 
 * @param keyWord - the current word the function is checking. 
 * 
 * @return true if success.
 * @return false if failed.
 */
bool isSymbol(LineNode* current);

/**
 * @brief checks if the line after a .struct is legal
 * 
 * @param keyWord - the first word the function is checking.
 * @param keyWord - the second word the function is checking.
 * @param head - the head node in the lines linked list.
 * @param current  - the current node in the lines linked list.
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return returnVal. 
 */
bool checkAfterStruct (LineNode* head, LineNode* current);

/**
 * @brief getRegister - checks if the keyword is a Register.
 * 
 * @param keyWord - the current word the function is checking.
 * 
 * @return int the enum number of the register, 0 if not found.
 */
int getRegister(char* keyWord);

/**
 * @brief isRegisterOrSymbol - checks of the keyWord is a symbol or a register. 
 * 
 * @param keyWord - the current word the function is checking.
 * 
 * @return int 1 if found a register or a symbol, 2 if found a symbol for an
 *      address call (for example 'S1' is a symbol so found 'S1.1'), and 0 if not found.
 */
int isRegisterOrSymbol(char* keyWord);

/**
 * @brief isDataStorage - checks of the keyWord is a data type reference.
 * 
 * @param keyWord - the current word the function is checking.
 * @param returnVal - holds the value the function needs to return.
 * @param wordLoc - holds the location of the keyword in the line (first if no symbol, second if a symbol has been found).
 * 
 * @return 1 if the key word is '.data'.
 * @return 2 if the key word is '.string'.
 * @return 3 if the key word is '.struct'.
 */
int isDataStorage(LineNode* current); /* .data = 1, .string = 2, .struct = 3, returns 0*/

/**
 * @brief addToMemory - adds data to memory space.
 * 
 * @param keyWord - the current word the function is checking. 
 * @param currentSymbol - the current node in the table linked list.
 * @param dataTypeNum - the return valse of isDataStorage.
 */
void addToMemory(LineNode* head, LineNode* current, int dataTypeNum);

/**
 * @brief isEntryGuidance - checks of the current is an entry.
 * 
 * @param keyWord - the current word the function is checking.
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return true if Entry.
 * @return false else.
 */
bool isEntryGuidance(LineNode* current);
/**
 * @brief isExternGuidance -checks of the current is an extern.
 * 
 * @param keyWord - the current word the function is checking.
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return true if external.
 * @return false else.
 */
bool isExternGuidance(LineNode* current);

/**
 * @brief checkLabel - check if the label already exist.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * 
 * @return true found that the label already exist.
 * @return false else.
 */
bool checkLabel(symbolEntryNode* symbolHead, char* symbol);

/**
 * @brief addToTable - adds a new label to the symbol table, create the linked list if there isn't one.
 * 
 * @param keyWord - the current word the function is checking. 
 * @param currentSymbol - the current node in the table linked list.
 * @param flag - a checker if the function can add the symbol to the table. 
 * @param duplicateVal - check duplicates.
 *  
 * @return true if symbol to added to table.
 * @return false else.
 */
bool addToTable(LineNode* head, LineNode* current, int wordLoc);

/**
 * @brief addExternalSymbol - adds en external symbol to the table, used in the second run stage.
 * 
 * @param currentSymbol - the current node in the table linked list. 
 */
void addExternalSymbol(LineNode* head, LineNode* current);

/**
 * @brief getDCval - get the memory size needed to add to DC value.
 * 
 * @param addDCcounter - counter to add to DC.
 * @param errCount - a self-check counter for errors.
 * @param negFlag - a bool flag for '-' to make sure the sign is legal.
 * @param commaFlag - a bool flag for ',' to make sure the sign is legal.
 * 
 * @return addDCcounter.
 */
int getDCval(LineNode* head, LineNode* current, char* keyWord, int dataTypeNum);

/**
 * @brief countCharForDC - received a string and checks if he's legal while count the chars in it.
 * 
 * @param addDCcounter - counter to add to DC aka the number for chars found.
 * @param errCount - a self-check counter for errors.
 * 
 * @return addDCcounter if the string is legal, else return 0.
 */
int countCharForDC(char* keyWord, int i);

/**
 * @brief countIntegersForDC - received an string and checks if he's legal while counting the amount of integers in it.
 * 
 * @param addDCcounter - counter to add to DC.
 * @param errCount - a self-check counter for errors.
 * @param negFlag - a bool flag for '-' to make sure the sign is legal.
 * @param commaFlag - a bool flag for ',' to make sure the sign is legal.
 * 
 * @return addDCcounter if the string is legal, else return 0.
 */
int countIntegersForDC(char* keyWord, int i);

/**
 * @brief IC_update to the IC values in each label in the symbol table.
 * 
 * @param currentSymbol - the current node in the table linked list.
 */
void IC_update(symbolEntryNode* symbolTable); /* line 17*/

/**
 * @brief getOpCodeInTable - get the opCode in line.
 * 
 * @param keyWord - the current word the function is checking.  
 * @param wordLoc - holds the location of the keyword in the line (first if no symbol, second if a symbol has been found).
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return returnVal.
 */
int getOpCodeInTable(LineNode* head, LineNode* current);

/**
 * @brief opStructureAnalysis - preform an analysis for the chars in the line after the opCode aka 'operands'.
 * 
 * @param opCodeNum - holds the witch opCode is in the line. 
 * @param addICcounter - holds the value that needed to add to IC.
 * @param errFlag - self - check if the function succeeded.
 * @param keyWord1 - the first word the function is checking.
 * @param keyWord2 - the second word the function is checking. 
 * @param keyWord3 - if isn't ==NULL then the line is illegal. 
 * 
 * 
 * @return addICcounter if errors have been found, else 0.
 */
int opStructureAnalysis(LineNode* head, LineNode* current);

/**
 * @brief two_Operation_Operands - check the validation of the operands keyWord1 and keyWord2.
 * 
 * @param keyWord1 - hold the value of the first operand.
 * @param keyWord2 - hold the value of the second operand.
 * @param firstOperand - counter for the first operand.
 * @param secondOperand - counter for the second operand.
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return returnVal if no errors have been found, else return 0.
 */
int two_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1, char* keyWord2);

/**
 * @brief one_Operation_Operands - check the validation of the operands keyWord1.
 * 
 * @param keyWord1 - hold the value of the first operand.
 * @param returnVal - holds the value the function needs to return.
 * 
 * @return returnVal if no errors have been found, else return 0.
 */
int one_Operation_Operands(LineNode* head, LineNode* current, int opCodeNum, char* keyWord1);

#endif