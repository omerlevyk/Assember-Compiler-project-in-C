#define MAX_SIZE_CHAR 256 /* max size of char*/
#define MAX_LINE_LENGTH 128 /* max length of a single line*/
#define IC_VALUE 100 /* the starting val of IC as per project instructions*/
#define MAX_WORDS_IN_LINE 4 /*max word allowed in a legal line in the file*/

#define ADDRESS_BIT_SIZE 2 /* the size needed for address bits length*/
#define OPCODE_BIT_SIZE 4 /* the size needed for opCode bits length*/
#define SYMBOL_BIT_SIZE 8 /* the size needed for symbol bits length*/
#define DATA_BIT_SIZE 10 /* the size needed for data bits length*/

/* enum type for boolean*/
typedef enum BOOL {
    FALSE,
    TRUE
} bool;

/* a struct type for a linked list, each node conation a single line from the input file*/
typedef struct LineNode {
    char* Content;
    struct LineNode* Next;
} LineNode;

/*  enum type for the symbolEntryNode type*/
typedef enum encodingType {
    entry = 0,
    external = 1,
    data = 2,
    noneEncoding = 3 /* for errors*/
} encodingType;

/*  another struct type for a linked list, this one is for the symbol table and each node conation a label*/
typedef struct symbolEntryNode {
    char* Name;
    char* Content;
    encodingType Type;
    int Address;
    LineNode* Next;
} symbolEntryNode;


/* enum type Commands opcode */
typedef enum opCode {
    opCodeErr = 0,  /* for errors*/
    /* two operands*/
    mov = 1,
    cmp = 2,
    add = 3,
    sub = 4,
    lea = 7,
    /* one operands*/
    nott = 5,
    clr = 6,
    inc = 8,
    dec = 9,
    jmp = 10,
    bne = 11,
    get = 12,
    prn = 13,
    jsr = 14,
    /* no operands*/
    rts = 15,
    hlt = 16
    
} opCode;

/* enum type for the registers*/
typedef enum registers {
    r0 = 1,
    r1 = 2,
    r2 = 3,
    r3 = 4,
    r4 = 5,
    r5 = 6,
    r6 = 7,
    r7 = 8
} registers;