
/*
class MacroManager - extractMacro(int stastMacroLineNumber, int endMacroLineNumber), getMacroByName()
class CodeValidator - extractSymbols(), ValidateLine(), getErrorDescription(), {fun to each operator (line 44)}
class code runner - nodeListCreator(), txtConvertor(), NumToBin(), operandValidator()
class file extract - fileExtractor()

Psudo for the process_file() {
* code = read file content
* code = macroManager.extractMacros(code)
* IC=0, DC=0

// replace macros calls with content (pre-run)
* for each line lineNumber
*   extractMacro()
*   if lineStr.isAMacro():
*       code.removeLine(lineNumber)
*       code.insertAt(lineNumber, macroManager.getMacro(lineStr))
*
*   extractMacto(int stastMacroLineNumber, int endMacroLineNumber):
        gets two int numbers, for the start line and end line, extract the macro and store it in an arry
        saveMacro() - adds the macro to a list

*   getMacroByName:
        int isMacro(char*) - if found a macro returns the loc in the array of the saved macro (if not found returns -1) 
        removeLine()
        get the macro from the list and insert it

// validator and symbols (first run)
* isSucceeded =true
* symTable = create two symbols table (one for names and one for decimal address)
* validator.extractSymbols(code, symTable)

* extractSymbols:
*   for each line lineStr:
*       create fun to each operator (mov, add, etc..) that identify the size needed for each op
*       
*   for each line lineStr:
*       errNum = validator.Validate(symTable)
*       if 0 != errNum:
*           fail! + validator.getErrorDescription(errNum)
*           isSucceeded =false
*   

// memory allocate
*    with allocate the memory space witch is IC*10 (IC = 136, 10 byte in each line)
*
// write and print code (second run)
*   nodeListCreator() // create a node list for all the external operands
*   for each line linStr:
*       txtConvertor(lineStr)
*       
*       
* txtConvertor:
*   - identify the operator and calculate the machine code number
*   - convert each line in binary with NumToBin((int) argv)
*   - attached the parts of the binary machine code
*     and adds them to the right location in the memory image
*   - adds the external operand to the node list for the external operands
*   - operandValidator(argv)
*
* operandValidator:
*   received the operand name and error check it
*       - if the operand name isn't in the symTable or the node list putout an error msg
*
*

// file extract(final code for printing)
*   for each file
*       fileExtractor()
*   after all input files has been worked on end program (return 0)
*
* fileExtractor:
*   create and extract all necessary files (.ob, .ext, .ent)
*
*
* }
*/