#include <iostream>
#include "lexer.h"
#include "paser.h"
#include "compiler.h"

using namespace std;

class Paser{
public:
    Node* program();
private:
    Lexer lexer;
    Token token;
    int lev;
    TokenType nextType();
    Node* funClosure();
    Node* fun();
    ParameterDecl* param_decl();
    DeclNode* decl();
    FunBody* fun_body();
};

Node* Paser::program(){
    token = lexer.GetToken();
    return paser_funClosure();
}

TokenType Paser::nextType(){
    token = lexer.GetToken();
    return token.type;
}

Node* Paser::funClosure(){
    if (token.isType() || token.type == VOID) {
        Node* nd = fun();
        Node* now = nd;
        now->next = NULL;
        while(token.isType() || token.type == VOID){
		    now->next = fun();
            now = now->next;
	    }
        return now;
    }
    if(token.type == END_OF_FILE) return NULL;
    Panic("Should be type but found");
}

Node* Paser::fun(){
    Node* nd = new Node;
    nd->type = Fun;
    FunNode* fun = nd->fun = new FunNode;
    fun->var.type = NULL;
    if(token.type != VOID){
        fun->var.type =  token.type == INT ? INT_TYPE : CHAR_TYPE;
    }
	if(nextType() != ID) {
        Panic("Should be ID");
    }
    fun->var.name = token.str;

	if(nextType() != LPAREN){
        Panic("Should be LPAREN");
    }

    fun->para = param_decl();
    if(nextType() != RPAREN){
        Panic("Should be RPAREN");
    }
    token = lexer.GetToken();
    if(token.type != LBRAC){
        fun->body = func_body();
        if(token.type != RBRAC){
            Panic("Should be RBRAC");
        }
        token = lexer.GetToken();
    }
    return nd;
}

Factor* Paser::factor(){
    Factor* f = NULL;
	if(token.type == LPAREN){
        f = new Factor;
		token = lexer.GetToken();
		f->expr = exp();
		if(token.type != RPAREN){
            Panic("Should be RPAREN");
        }
	}
	else if(token.type == ID){
        f = new Factor;
		f->var = var_func_call();
	}
	else if(token.type == NUM){
        f = new Factor;
        f->num = atoi(token.str);
	}
    else if(token.type == CHAR){
        f = new Factor;
        f->c = token.str[0];
    }
	else{
		Panic("Factor error");
	}
    return f;
}

VarOrFunCall* Paser::var_func_call(){
	if(token.type != ID){
        Panic("Should be ID");
	}
    VarOrFunCall* nd = new VarOrFunCall;
    nd->var.name = token.str;
    nd->funSuf = func_call_suffix();
    return nd;
}

FunSuffix* Paser::func_call_suffix(){
	if(token.type == LPAREN){

    FunSuffix* nd = new 
		nd-> vars = param_list();
		if(token.type==RPAREN){
			token = lexer.GetToken();
		}
		else{
			Panic();
		}
	}
}
Expression* Paxer::exp(){
    Expression* e = new Expression;
	e->facC = factor_combine();
	e->term = term();
    return e;
}
FactorCombine* Paxer::factor_combine(){
    FactorCombine* fc = new FactorCombie;
	fc->fac = factor();
	fc->rec = factor_recur();
    return fc;
}

FactorRecur* Paxer::factor_recur(){
    FactorRecur* fr = new FactorRecur;
    FactorRecur* now = fr;
	while(token.type == MULT || token.type == DIV || token.type == MOD){
        now->op = token.str[0];
        now->facC = factor();
        now = now->facC;
        token = lexer.GetToken();
	}
    return fr;
}

Term* Paxer::term(){
    Term* nd = new Term;
    Term* t = nd;
	while(token.type == PLUS || token.type == MINUS){
        t->op = token.str[0];
		t->facC = factor_combine();
        t->term = new Term;
        t = t->term;
	}
    return nd;
}

ParameterDecl* Paser::param_decl(){
    token = lexer.GetToken();
	if(token.isType()){
        ParameterDecl* nd = new ParameterDecl;
		nd->decNode = decl();
		while(nextType() == COMMA){
			nd->next = decl(); 
            nd = nd->next;
		}
        lexer.PushToken(token);
        return nd;
	}
    if(token.type == VOID) return ParameterDecl();
    return NULL;
}

DeclNode* Paser::decl(){
    DeclNode* dec = new DeclNode;
	dec->type = token.type == INT ? INT_TYPE : CHAR_TYPE;
    if(nextType() != ID){
        Panic("Should be ID");
    }
    dec->name = token.str;

	if(nextToken.type == EQUAL){
        if(nextToken() == ASSIGN){
		    dec->assign = expr();
        }else{
            lexer.PushToken(token);
        }
	}
    return dec;
}

FunBody* Paser::fun_body(){
    FunBody* fun = new FunBody;
    fun->decl = decl_sentence_clos();
	fun->next = fun_body_clos();
}

DeclStmtClosure* Paser::decl_sentence_clos(){
    DeclStmtClosure* nd = new DeclStmtClosure;
    if(token.isType()){
        nd->decl = decl_sentence();
        while(token.isType()){
            nd->next = decl_sentence();
            nd = nd->next;
        }
    }
}

DeclStmtClosure* Paxer::decl_sentence(){
	decl();
	if(token.type==SEMICOLON){
		token = lexer.GetToken();
	}
	else{
		Panic();
	}
}

Node* Paxer::fun_body_clos(){
    Node * nd = NULL;
    if(token.type == ID || token.type == FOR || token.type == IF || token.type == RETURN){
        
        while(token.type == ID || token.type == FOR || token.type == IF || token.type == RETURN){
            
            switch(token.type){
                case ID:assign_func();break;
                case FOR:for_loop();break;
                case IF:if_sentence();break;
                case RETURN:func_return();break;
                default:break;
            }
        }
    }
}

 assign_func(){
	var();
	assign_func_call();
}
void assign_func_call(){
	if(token.type==EQUAL){
		token = lexer.GetToken();
		right_value();
		if(token.type==SEMICOLON){
			token = lexer.GetToken();
		}
		else{
			Panic();
		}
	}
	else if(token.type==LPAREN){
		token = lexer.GetToken();
		param_list();
		if(token.type==RPAREN){
			token = lexer.GetToken();
			if(token.type==SEMICOLON){
				token = lexer.GetToken();
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}
void param_list(){
	param();
	param_clos();
}
void param_clos(){
	while(token.type==COMMA){
		token = lexer.GetToken();
		param();
	}
}

void param(){
	if(token.type==ID || token.type==NUM){
		token = lexer.GetToken();
	}
	else{
		Panic();
	}
}

void for_loop(){
	if(token.type==FOR){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			assign_func();
			logic_exp();
			if(token.type==SEMICOLON){
				token = lexer.GetToken();
				suffix_exp();
				if(token.type==RPAREN){
					token = lexer.GetToken();
					if(token.type==LBRAC){
						token = lexer.GetToken();
						fun_body();
						if(token.type==RBRAC){
							token = lexer.GetToken();
                            return;
						}
						Panic();
					}
					else{
						Panic();
					}
				}
				else{
					Panic();
				}
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}
void mutiple_logic_exp(){
	logic_exp();
	mutiple_logic_exp_recur();
}
void mutiple_logic_exp_recur(){
	if(token.type==AND||token.type==OR){
		token = lexer.GetToken();
		mutiple_logic_exp();
	}
}
void adv_logic_sym(){
	if(token.type==AND||token.type==OR){
		token = lexer.GetToken();
	}
	else{
		Panic();
	}
}
void logic_exp(){
	exp();
	logic_exp_recur();
}
void logic_exp_recur(){
	if(token.type==LESS||token.type==LESSEQUAL||token.type==GREATER||token.type==GREATEREQUAL||token.type==EQUAL||token.type==NOTEQUAL){
		token = lexer.GetToken();
		logic_exp();
	}
}
void logic_sym(){
	if(token.type==LESS||token.type==LESSEQUAL||token.type==GREATER||token.type==GREATEREQUAL||token.type==EQUAL||token.type==NOTEQUAL){
		token = lexer.GetToken();
	}
	else{
		Panic();
	}
}
void suffix_exp(){
	var();
	suffix_sym();
}
void suffix_sym(){
	if(token.type==PLUS2||token.type==MINUS2){
		token = lexer.GetToken();
	}
	else{
		Panic();
	}
}
void if_sentence(){
	if(token.type==IF){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			mutiple_logic_exp();
			if(token.type==RPAREN){
				token = lexer.GetToken();
				if(token.type==LBRAC){
					token = lexer.GetToken();
					fun_body();
					if(token.type==RBRAC){
						token = lexer.GetToken();
						else_sentence();
					}
					else{
						Panic();
					}
				}
				else{
					Panic();
				}
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}
void else_sentence(){
	if(token.type==ELSE){
		token = lexer.GetToken();
		if(token.type==LBRAC){
			token = lexer.GetToken();
			fun_body();
			if(token.type==RBRAC){
				token = lexer.GetToken();
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
}
void func_return(){
	if(token.type==RETURN){
		token = lexer.GetToken();
		factor();
		if(token.type==SEMICOLON){
			token = lexer.GetToken();
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}
void scan_sentence(){
	if(token.type==SCAN){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			if(token.type == ID) {
                token = lexer.GetToken();
            }
			if(token.type==RPAREN){
				token = lexer.GetToken();
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}
void print_sentence(){
	if(token.type==PRINT){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			if(token.type==ID||token.type==NUM||token.type==CHAR){
				var();
				if(token.type==RPAREN){
					token = lexer.GetToken();
				}
				else{
					Panic();
				}
			}
			else if(token.type==STRING){
				string();
				if(token.type==RPAREN){
					token = lexer.GetToken();
				}
				else{
					Panic();
				}				
			}
			else{
				Panic();
			}
		}
		else{
			Panic();
		}
	}
	else{
		Panic();
	}
}

void Panic(string info){
    cout << info << ": ";
    token.Print();
}

int main() {
    token = lexer.GetToken();
    func();
}
