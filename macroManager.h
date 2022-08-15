#include "globalFun.h"
#include "LinesManager.h" 


/**
 * @brief macroManager - governs the first stage. reserved the lines linked list,
 *      removes all the macro definition and insert it in the macro call spaces.
 * 
 * @param currentIndex - a counter for the line number.
 * @param currentLine - tracks the current node in the linked list.
 * @param macroCount - counter of the number of macros in the file.
 * @param macroNames - a char that saved the names of the macros.
 * @param macros - saved the macro definition.
 * 
 * @returnTRUE - if this stage is success and the program can continue the the next stage.
 * @returnFALSE - if this stage have failed and the program needs to stop.
 */
bool macroManager(LineNode* head); /* pre-run*/

/**
 * @brief findMacros - fined a macro definition and store it in 'macros' while update 'macroCount' and 'macroNames'.
 * 
 * @param current -  tracks the current node in the linked list.
 * @param perv - tracks the last node in the linked list.
 * @param keyWord - the current word the function is checking.
 */
void findMacros(LineNode* head);

/**
 * @brief deleteLocalArrays - delete all the local array at the end of the stage
*/
void deleteLocalArrays(); /* populate the local arrays with macro definitions*/

/**
 * @brief check of this line has a macro call Name 
 * 
 * @param lineContent - holds the content of a single line.
 * 
 * @return if the line is a macro call return its name, otherwise return NULL.
 */
char* getMacroCallName(char* lineContent);

/**
 * @brief Get the Macro call location as per the line number they're at.
 * 
 * @param macroName - the name of the macro.
 *
 *  @return int index in the local arrays of this macro definition.
 */
int getMacroIndex(char* macroName);