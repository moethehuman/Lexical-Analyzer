// front.cpp - lexical analyzer for simple arithmetic expressions (no input file)

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_INPUT -1

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

// Global variables
int charClass;
string lexeme;
char nextChar;
int nextToken;
string input;
int pos = 0;

// Function declarations
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

// addChar - Adds nextChar to lexeme
void addChar() {
    if (lexeme.length() <= 98) {
        lexeme += nextChar;
    }
    else {
        cout << "Error - lexeme is too long\n";
    }
}

// getChar - Gets the next character from the input string
void getChar() {
    if (pos < input.length()) {
        nextChar = input[pos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_INPUT;
    }
}

// getNonBlank - Skips whitespace
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

// lookup - Identifies operators and parentheses
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = END_OF_INPUT;
        break;
    }
    return nextToken;
}

// lex - Lexical analyzer
int lex() {
    lexeme = "";
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case END_OF_INPUT:
        nextToken = END_OF_INPUT;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

// main - Driver function
int main() {
    cout << "Enter an expression: ";
    getline(cin, input);

    pos = 0;
    getChar();
    do {
        lex();
    } while (nextToken != END_OF_INPUT);

    return 0;
}