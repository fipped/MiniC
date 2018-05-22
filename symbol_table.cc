#include "symbol_table.h"

Variable* SymbolTable::get(std::string symbol) {
    return symbol_table[symbol];
}

Variable* SymbolTable::set(std::string symbol, VarType type, void* val, int lev) {
    if(symbol_table[symbol] == NULL) {
        symbol_table[symbol] = new Value;
        symbol_table[symbol]->name = symbol;
    }
    symbol_table[symbol]->val = val;
    symbol_table[symbol]->type = type;
    symbol_table[symbol]->lev = lev;
    return symbol_table[symbol];
}
