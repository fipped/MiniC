#include "lexer.h"
#include <iostream>
#include<stdio.h>

using namespace std;

std::string TokenName[] = {
    "ERROR", "if", "else", "while", "for",
    "switch", "case", "default",
    "break", "return",
    "void", "int", "char",
    "scan", "print",
    "STRING",
    "+", "-", "/", "*", "%", "++", "--", "=",
    "&&", "||",
    "==", ">", ">=", "<", "<=", "!=",
    "{", "}", "(", ")", "[", "]", ":", ",", ";",
    "NUM", "ID", "EOF",
};
std::string reserve_list[] = {
    "if", "else", "while", "for",
    "switch", "case", "default",
    "break", "return",
    "void", "int", "char",
    "scan", "print",
};
Lexer::Lexer(){
    line = 1;
}

void Token::Print(){
    cout << "token: ";
    switch (type){
        case ID:case NUM: cout << str; break;
        case CHAR: cout << "'" << str << "'"; break;
        case STRING: cout << '"' << str << '"'; break;
        default:
            cout << TokenName[type]; break;
    }
    cout << " at line " << line << endl;
}

bool Token::isType(){
    return type == INT || type == CHAR;
}

Token Lexer::GetToken(){
    if(tokens.size()){
        Token t = tokens.back();
        tokens.pop_back();
        return t;
    }
    char ch = nextChar();
    while(isSpace(ch)){
        if(isNewLine(ch)) line++;
        ch = nextChar();
    }
    token.line = line;
    token.type = ERROR;
    token.str = "";
    switch(ch){
        case EOF: token.type = END_OF_FILE; return token;
        case '!':
            ch = nextChar();
            if(ch == '='){
                token.type = NOTEQUAL;
                return token;
            }
            pushChar(ch);
            return token;
        case '=':
            ch = nextChar();
            if(ch == '='){
                token.type = EQUAL;
                return token;
            }
            pushChar(ch);
            token.type = ASSIGN;
            return token;
        case '<':
            ch = nextChar();
            if(ch == '='){
                token.type = LESSEQUAL;
                return token;
            }
            pushChar(ch);
            token.type = LESS;
            return token;
        case '>':
            ch = nextChar();
            if(ch == '='){
                token.type = GREATEREQUAL;
                return token;
            }
            pushChar(ch);
            token.type = GREATER;
            return token;
        case '+':
            ch = nextChar();
            if(ch == '+'){
                token.type = PLUS2;
                return token;
            }
            pushChar(ch);
            token.type = PLUS;
            return token;
        case '-':
            ch = nextChar();
            if(ch == '-'){
                token.type = MINUS2;
                return token;
            }
            pushChar(ch);
            token.type = MINUS;
            return token;
        case '&':
            ch = nextChar();
            if(ch == '&'){
                token.type = AND;
                return token;
            }
            pushChar(ch);
            return token;
        case '|':
            ch = nextChar();
            if(ch == '|'){
                token.type = OR;
                return token;
            }
            pushChar(ch);
            return token;
        case '/': token.type = DIV; return token;
        case '*': token.type = MULT; return token;
        case ':': token.type = COLON; return token;
        case ';': token.type = SEMICOLON; return token;
        case ',': token.type = COMMA; return token;
        case '(': token.type = LPAREN; return token;
        case ')': token.type = RPAREN; return token;
        case '{': token.type = LBRAC; return token;
        case '}': token.type = RBRAC; return token;
        case '%': token.type = MOD; return token;
        case '[': token.type = LBRACE; return token;
        case ']': token.type = RBRACE; return token;
        case '\'':
            ch = nextChar();
            if(ch == '\'') return token;
            token.str += ch;
            if(ch == '\\'){
                token.str += ch;
            }
            if(nextChar()!='\''){
                token.str = "";
                return token;
            }
            token.type = CHAR;
            return token;
        case '"': {
            ch = nextChar();
            int len = 0;
            while(ch!='"'){
                token.str += ch;
                if(ch == '\\'){
                    ch = nextChar();
                    if(ch != EOF) token.str += ch;
                }
                ch = nextChar();
                // The length of the string should not exceed 1024.
                if(len++ > str_max_len) {
                    token.str = "";
                    return token;
                }
            }
            token.type = STRING;
            return token;
        }
        default:
            if(isDigit(ch)){
                while(isDigit(ch)){
                    token.str += ch;
                    ch = nextChar();
                }
                if(ch!=EOF) pushChar(ch);
                token.type = NUM;
            }
            else if(isLetter(ch)){
                while(isLetter(ch)||isDigit(ch)){
                    token.str += ch;
                    ch = nextChar();
                }
                if(ch!=EOF) pushChar(ch);
                token.type = reserver();
                if(token.type == 0){
                    token.type = ID;
                }
            }
            else if(ch == EOF){
                token.type = END_OF_FILE;
            }
            return token;
    }
}

void Lexer::PushToken(Token t){
    tokens.push_back(t);
}

bool Lexer::isSpace(char ch){
    return ch == ' ' || ch == '\t' || ch == '\n' || ch =='\r';
}

bool Lexer::isNewLine(char ch){
    return ch == '\n';
}

bool Lexer::isDigit(char ch){
    return (ch>='0'&&ch<='9');
}

bool Lexer::isLetter(char ch){
    return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

TokenType Lexer::reserver(){
    for(int i=0;i<reserve_num;i++)
        if(token.str == reserve_list[i])
            return (TokenType)(i+1);
    return ERROR;
}

char Lexer::nextChar(){
    if(buffer.empty()) return getchar();
    char ch = buffer.back();
    buffer.pop_back();
    return ch;
}

void Lexer::pushChar(char ch){
    buffer.push_back(ch);
}

// int main(){
//     Lexer lexer;
//     Token token = lexer.GetToken();
//     token.Print();
//     while(token.type != END_OF_FILE){
//         token=lexer.GetToken();
//         token.Print();
//     }
//     return 0;
// }
