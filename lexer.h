#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
#include <string>
#include <vector>

// token
typedef enum {
    // , if, else, while, for
    ERROR, IF, ELSE, WHILE, FOR, 
    // switch, case, deafult,
    SWITCH, CASE, DEFAULT,
    // break, return
    BREAK, RETURN,
    // void, int, char
    VOID, INT, CHAR,
    // scan, print
    SCAN, PRINT,
    STRING,
    //+，-，/，*，%，++，--，=，
    PLUS, MINUS, DIV, MULT, MOD, PLUS2, MINUS2, ASSIGN,
    //&&，||
    AND, OR, 
    // ==，>，>=，<，<=，!=
    EQUAL, GREATER, GREATEREQUAL, LESS, LESSEQUAL, NOTEQUAL,
    // {, }, (, ), [, ], :, ',', ;,
    LBRAC, RBRAC, LPAREN, RPAREN, LBRACE, RBRACE, COLON, COMMA, SEMICOLON, 
    NUM, ID, END_OF_FILE
} TokenType;

extern std::string TokenName[];
extern std::string reserve_list[];
const int reserve_num = 14;
const int str_max_len = 1024;
class Token {
public:
    Token(){type=ERROR;line=1;str="";}
    TokenType type;
    int line;
    std::string str;
    void Print();
    bool isType();
};

class Lexer {
public:
    Lexer();
    Token GetToken();
    void PushToken(Token token);
private:
    std::vector<Token> tokens;
    std::string buffer;
    char nextChar();
    void pushChar(char ch);
    Token token;
    int line;
    bool isSpace(char ch);
    bool isNewLine(char ch);
    bool isDigit(char ch);
    bool isLetter(char ch);
    TokenType reserver();
};
#endif //LEXER_H_INCLUDED
