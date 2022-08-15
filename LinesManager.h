#include "globalFun.h"
#include "secondRun.h"

/**
 * @brief LoadFile - Load file from path 
 * 
 * @param fp - hold the input file.
 * @param fpFileName - holds the file name.
 * @param line - a char that holds a single line from the file.
 * @param head - the head node in the lines linked list.
 * @param current - the current node in the lines linked list.
 * 
 * @return LineNode* head - the head of the line linked list.
 */
LineNode* LoadFile(char* path);

/**
 * @brief CopyLines - copy the content a line node. 
 * 
 * @param current - the current node in the lines linked list.
 * @param section - a copied node of current.
 * 
 * @return LineNode* section.
 */
LineNode* CopyLines(LineNode* head);

/**
 * @brief addNewNode - create a new node and link it as a new last node.
 * 
*  @param current - the current node in the lines linked list.
 * @param newNode - the new node.
 */
void addNewNode(LineNode* head, char* Content);

/**
 * @brief DeleteAllLines - delete all the nodes at the end of the program.
 * 
 * @param current - the current node in the lines linked list.
 * @param next - the next node in the lines linked list.
 */
void DeleteAllLines(LineNode* head);

/**
 * @brief closeAllSystems - delete all left pointers at the end of the program.
 * 
 * @param currentSymbol - the current node in the table linked list.
 * @param NextSymbol - the next node in the table linked list.
 */
void closeAllSystems(LineNode* head, LineNode* binHead);

/**
 * @brief GetFileLength - get the number of lines in the node list (originally from a file).
 * 
 * @param current - the current node in the lines linked list.
 * @param lineNumCounter - a counter for the line numbers.
 * 
 * @return int lineNumCounter.
 */
int GetFileLength(LineNode* head);

/**
 * @brief getLineNumber - get the line Number of a specific node.
 * 
 * @param current - the current node in the lines linked list.
 * @param lineNumCounter - a counter for the line numbers.
 * 
 * @return int lineNumCounter, 0r -1 if not found. 
 */
int getLineNumber(LineNode* head, LineNode* nodeLoc);

/**
 * @brief ExtractLines - extract a selected amount of lines and store them in 'section'.
 * 
 * @param current - the current node in the lines linked list.
 * @param prev - the previous node in the lines linked list.
 * @param section - a node that contain the extracted node.
 * 
 * @return section.
 */
LineNode* ExtractLines(LineNode* head, int fromLine, int length);

/**
 * @brief DeleteAt - delete a selected node form the linked list,
 *      can remove more then one at a time in the condition they are next to each other.
 * 
 * @param current - the current node in the lines linked list.
 * @param prev - the previous node in the lines linked list.
 */
void DeleteAt(LineNode* head, int index, int linesAmount);

/**
 * @brief InsertLinesSection - insert a single or multiple nodes in a selected location at the linked list.
 * 
 * @param current - the current node in the lines linked list.
 * @param prev - the previous node in the lines linked list.
 * 
 * @return LineNode* head.
 */
LineNode* InsertLinesSection(LineNode* head, LineNode* section, int insertAt);

/**
 * @brief getWord - get a single word from a select location in the line content from a givin node.
 * 
 * @param strLine - holds the word as a char.
 * 
 * @returnTRUE if found,
 * @returnFALSE otherwise.
 */
bool getWord(LineNode* current, int wordLoc, char* ch);
/**
 * @brief getLineFromPoint - gets the line from a choosen loc
 * 
 * @returnTRUE if found,
 * @returnFALSE otherwise.
 */
bool getLineFromPoint(LineNode* current, int wordLoc, char* strLine);

/**
 * @brief getErroDescription - a switch case function that fprintf the Error Description. 
 * 
 */
void getErrorDescription(LineNode* head, LineNode* current, char* ch, int errNum);