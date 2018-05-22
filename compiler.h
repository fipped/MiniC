#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED
#include <string>

typedef enum {
    Void_Type,
    Int_Type, 
    Char_Type, 
}VarType;

typedef enum {
    Fun,
    DeclStmt,
    AssignStmt,
    ForStmt,
    IfStmt,
    ReturnStmt,
    PrintStmt,
    ScanStmt,
}NodeType;


class Node{
    Node* next;
    NodeType type;
    union {
        FunNode* fun;
        DeclStmtNode* decl;
        AssignStmtNode* assign;
        ForStmtNode* fors,
        IfStmtNode* cond,
        ReturnStmtNode* ret,
        PrintStmtNode* print,
        ScanStmtNode* scan
    }
};

class FunNode{
    Variable var;
    ParameterDecl* para; 
    FunBody* body;
};

class ParameterDecl{
    DeclNode * decNode;
    DeclClosureNode * decCloNode;
    bool void;
};

class Variable{
    std::string name;// 变量名
    VarType     type;// 类型
    void*       val; // 值
    int         lev; // 层数
    int         adr; // 地址
};

class Factor{
    Expression* expr;
    VarOrFunCall* var;
    VarType type;
    union{
        int num;
        char c;
    }
};

class Expression{
    FactorCombine* facC;
    Term* term;
};

class VarOrFunCall{
    Variable* var;
    FunSuffix* funSuf;
};

class FunSuffix{
    VariableList* vars;
};

class FactorCombine{
    Factor* fac;
    FactorRecur* rec;
};

class FactorRecur{
    char op;
    FactorCombine* facC;
};

class Term{
	char op;
	FactorCombine * facC;
	Term * term;
};

class ParameterDeclNode{
	DeclNode * decNode;
	DeclClosureNode * decCloNode;
	bool void;
};

class DeclNode{
	VarType type;
	VariableNode * varNode;
	AssignNode * assign;
};

class DeclClosureNode{
	DeclNode * decNode;
	DeclNode * next;		
};

class FunBody {
    DeclStmtClosure* decl;
    Node* next; 
};

class DeclStmtClosure{
    DeclNode* decl;
    DeclStmtClosure* next;
};

class FunClosureNode{
	Node* next;
	NodeType nodeType;
	union{
		Node* assignNode;
		Node* forNode;
		Node* conNode;
		Node* retNode;
	}
	FunClosureNode* funNode;
};

class DeclStmtClosureNode{
	Node* next;
	DeclStmtClosureNode* decStmtNode;
};

DeclStmt Node;

AssignStmt Node;

class AssignOrFunCallNode{
	union{
		RightValNode* rightNode;
		ParameterListNode* parListNode;
	}
};



#endif //COMPILER_H_INCLUDED
