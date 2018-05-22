#include <iostream>
#include "lexer.h"
#include "paser.h"

using namespace std;
Lexer lexer;
Token token;
void func(){
	sub_func_clos();
}
void sub_func_clos(){
    if (token.type==VOID||token.type==INT||token.type==CHAR) {
	    while(token.type==VOID||token.type==INT||token.type==CHAR){
		    sub_func();
	    }
    }else {
        Panic("should be type");
    }
}
void sub_func(){
	if(token.type==VOID||token.type==INT||token.type==CHAR){
		token = lexer.GetToken();
		var();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			param_decl();
			if(token.type==RPAREN){
				token = lexer.GetToken();
				if(token.type==LBRAC){
					token = lexer.GetToken();
					func_block();
					if(token.type==RBRAC){
						token = lexer.GetToken();
					}
					else{
						Panic("should be }");
					}
				}
				else{
					Panic("should be {");
				}
			}
			else{
				Panic("should be )");
			}
		}
		else{
			Panic("should be (");
		}
	}
	else{
		Panic("should be type or void");
	}
}
void type(){
	if(token.type==INT||token.type==CHAR){
		token = lexer.GetToken();
	}
	else{
		Panic("should be int or char");
	}
}
void var(){
	if(token.type==ID){
		token = lexer.GetToken();
	}
	else{
		Panic("should be ID");
	}
}
void factor(){
	if(token.type==LPAREN){
		token = lexer.GetToken();
		exp();
		if(token.type==RPAREN){
			token = lexer.GetToken();
		}	
		else{
			Panic("should be )");
		}
	}
	else if(token.type==ID){
		var_func_call();
	}
	else if(token.type==NUM){
		token = lexer.GetToken();
	}
	else if(token.type==CHAR){
		token = lexer.GetToken();
	}	
	else{
		Panic("should be ( or ID or num or char");
	}
}
void var_func_call(){
	if(token.type==ID){
		var();
		func_call_suffix();
	}
	else{
		Panic("should be ID");
	}
}
void func_call_suffix(){
	if(token.type==LPAREN){
		token = lexer.GetToken();
		param_list();
		if(token.type==RPAREN){
			token = lexer.GetToken();
		}
		else{
			Panic("should be (");
		}
	}
}
void exp(){
	factor_combine();
	term();
}
void factor_combine(){
	factor();
	factor_recur();
}
void factor_recur(){
	while(token.type==MULT||token.type==DIV||token.type==MOD){
		factor();
	}
}
void term(){
	while(token.type==PLUS||token.type==MINUS){
		factor_combine();
	}
}
void param_decl(){
	if(token.type==INT||token.type==CHAR){
		decl();
		if(token.type==COMMA){
			decl_clos(); 
		}
	}
	else if(token.type==VOID){
		token = lexer.GetToken();
	}
}
void decl(){
	type();
	var();
	if(token.type==ASSIGN){
		assign();
	}
}
void assign(){
	if(token.type==ASSIGN){
		token = lexer.GetToken();
		right_value();
	}
}
void right_value(){
	exp();
}
void decl_clos(){
	while(token.type==COMMA){
		token = lexer.GetToken();
		decl();
	}
}
void func_block(){
	token.Print();
	decl_sentence_clos();
	func_block_clos();
}
void decl_sentence_clos(){
	while(token.type==INT||token.type==CHAR){
		decl_sentence();
	}
}
void decl_sentence(){
	decl();
	if(token.type==SEMICOLON){
		token = lexer.GetToken();
	}
	else{
		Panic("should be ;");
	}
}
void func_block_clos(){
	while(token.type==ID||token.type==FOR||token.type==IF||token.type==RETURN||token.type==SCAN||token.type==PRINT){
		switch(token.type){
			case ID:assign_func();break;
			case FOR:for_loop();break;
			case IF:if_sentence();break;
			case RETURN:func_return();break;
			case SCAN:scan_sentence();break;
			case PRINT:print_sentence();break;
			default:token = lexer.GetToken();break;
		}
	}
}
void assign_func(){
	var();
	assign_func_call();
}
void assign_func_call(){
	if(token.type==ASSIGN){
		token = lexer.GetToken();
		right_value();
		if(token.type==SEMICOLON){
			token = lexer.GetToken();
		}
		else{
			Panic("should be ;");
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
				Panic("should be ;");
			}
		}
		else{
			Panic("should be )");
		}
	}
	else{
		Panic("should be == or (");
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
	if(token.type==ID || token.type==NUM || token.type==CHAR){
		token = lexer.GetToken();
	}
	else{
		Panic("should be ID or num or char");
	}
}
void parse_string(){
	if(token.type==STRING){
		token = lexer.GetToken();
	}
	else{
		Panic("should be string");
	}
}
void for_loop(){
	if(token.type==FOR){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			if(token.type==INT){
				token = lexer.GetToken();
			}
			assign_func();
			logic_exp();
			if(token.type==SEMICOLON){
				token = lexer.GetToken();
				suffix_exp();
				if(token.type==RPAREN){
					token = lexer.GetToken();
					if(token.type==LBRAC){
						token = lexer.GetToken();
						func_block();
						if(token.type==RBRAC){
							token = lexer.GetToken();
						}
						else{
							Panic("should be }");
						}
					}
					else{
						Panic("should be {");
					}
				}
				else{
					Panic("should be )");
				}
			}
			else{
				Panic("should be ;");
			}
		}
		else{
			Panic("should be (");
		}
	}
	else{
		Panic("should be for");
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
		Panic("should be && or ||");
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
		Panic("should be < or <= or > or >= or == or !=");
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
		Panic("should be ++ or --");
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
					func_block();
					if(token.type==RBRAC){
						token = lexer.GetToken();
						else_sentence();
					}
					else{
						Panic("should be }");
					}
				}
				else{
					Panic("should be {");
				}
			}
			else{
				Panic("should be )");
			}
		}
		else{
			Panic("should be (");
		}
	}
	else{
		Panic("should be if");
	}
}
void else_sentence(){
	if(token.type==ELSE){
		token = lexer.GetToken();
			if(token.type==LBRAC){
			token = lexer.GetToken();
			func_block();
			if(token.type==RBRAC){
				token = lexer.GetToken();
			}
			else{
				Panic("should be }");
			}
		}
		else{
			Panic("should be {");
		}
	}
	else{
		Panic("should be else");
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
			Panic("should be ;");
		}
	}
	else{
		Panic("should be return");
	}
}

void scan_sentence(){
	if(token.type==SCAN){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();

			if(token.type == ID) {
               			token = lexer.GetToken();	
				if(token.type==RPAREN){
					token = lexer.GetToken();
					if(token.type==SEMICOLON){
						token = lexer.GetToken();
					}
					else{
						Panic("should be ;");
					}
				}
				else{
					Panic("should be )");
				}
			}
			else{
				Panic("should be ID");
			}
		}
		else{
			Panic("should be (");
		}
	}
	else{
		Panic("should be scan");
	}
}
void print_sentence(){
	if(token.type==PRINT){
		token = lexer.GetToken();
		if(token.type==LPAREN){
			token = lexer.GetToken();
			if(token.type==INT||token.type==CHAR){
				var();
				if(token.type==RPAREN){
					token = lexer.GetToken();
					if(token.type==SEMICOLON){
						token = lexer.GetToken();
					}
					else{
						Panic("should be ;");
					}
				}
				else{
					Panic("should be )");
				}
			}
			else if(token.type==STRING){
				string();
				if(token.type==RPAREN){
					token = lexer.GetToken();
				}
				else{
					Panic("should be )");
				}				
			}
			else{
				Panic("should be int or char or string");
			}
		}
		else{
			Panic("should be (");
		}
	}
	else{
		Panic("should be print");
	}
}
void Panic(string info){
	cout << info << ": ";
	token.Print();
	exit(0);
}

int main() {
     token = lexer.GetToken();
     func();
}
