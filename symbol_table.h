#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED
#include <vector>
#include <unordered_map>
#include "compiler.h"

class SymbolTable {
public:
    Variable* get(std::string symbol);
    Variable* set(std::string symbol, VarType type, void* val, int lev);
private:
    std::unordered_map<std::string, Variable*>symbol_table;
};

#endif //SYMBOL_TABLE_H_INCLUDED
