#ifndef PASER_H_INCLUDED
#define PASER_H_INCLUDED
#include <string>
#include <cstdlib>
#include <cstdio>
// _Program_           → _FunClosure_
void func();

// _FunClosure_        → _ _FunClosure_
// _FunClosure_        → ε
void sub_func_clos();

// _Function_          → _Type_ _Variable_(_ParameterDecl_){_FunctionBody_}
// _Function_          → void _Variable_(_ParameterDecl_){_FunctionBody_}
void sub_func();

// _Type_              → int | char
void type();

// _Variable_          → ID
void var();

// _Factor_            → (_Expression_)
// _Factor_            → _VariableOrFunCall_
// _Factor_            → _NumClosure_
void factor();

// _VariableOrFunCall_ → _Variable_ _FunSuffix_
void var_func_call();

// _FunSuffix_         → (_VariableList_) | ε
void func_call_suffix();

// _Expression_        → _Term_ OPERATOR
void exp();

// _FactorCombine_     → _Factor_ _FactorRecur_
void factor_combine();

// _FactorRecur_     → * _Factor_ _FactorRecur_
// _FactorRecur_     → / _Factor_ _FactorRecur_
// _FactorRecur_     → % _Factor_ _FactorRecur_
// _FactorRecur_     → ε
void factor_recur();

// _Term_              → + _FactorCombine_ _Term_
// _Term_              → - _FactorCombine_ _Term_
// _Term_              → ε
void term();

// _ParameterDecl_     → _Decl_ _DeclClosure_ | void | ε
void param_decl();

// _Decl_              → _Type_ _Variable_ _Assign_
void decl();


// _Assign_            → _RightVal_ | ε
void assign();

// _RightVal_          → _Expression_
void right_value();

// _DeclClosure_       → , _Decl_ _DeclClosure_ | ε
void decl_clos();
//【声明闭包】 》 , 【声明】 【声明闭包】
//【声明闭包】 》 $
void func_block();
//【函数块】 》 【声明语句闭包】 【函数块闭包】
void decl_sentence_clos();
//【声明语句闭包】 》 【声明语句】 【声明语句闭包】
//【声明语句闭包】 》 $
void decl_sentence();
//【声明语句】 》 【声明】 ;
void func_block_clos();
//【函数块闭包】 》 【赋值函数】 【函数块闭包】
//【函数块闭包】 》 【for循环】 【函数块闭包】
//【函数块闭包】 》 【条件语句】 【函数块闭包】
//【函数块闭包】 》 【函数返回】 【函数块闭包】
//【函数块闭包】 》  $
void assign_func();
//【赋值函数】 》 【变量】 【赋值或函数调用】
void assign_func_call();
//【赋值或函数调用】 》 = 【右值】 ;
//【赋值或函数调用】 》 ( 【参数列表】 ) ;
void param_list();
//【参数列表】 》 【参数】 【参数闭包】
void param_clos();
//【参数闭包】 》 , 【参数】 【参数闭包】
//【参数闭包】 》 $
void param();
//【参数】 》 【标志符】
//【参数】 》 【数字闭包】
void parse_string();
//【字符串】 》 string
void for_loop();
//【for循环】 》 for ( 【赋值函数】 【逻辑表达式】 ; 【后缀表达式】 ) { 【函数块】 }
void mutiple_logic_exp();
//【多重逻辑表达式】 》 【逻辑表达式】 【多重逻辑表达式递归】
void mutiple_logic_exp_recur();
//【多重逻辑表达式递归】 》 【高级逻辑运算符】 【多重逻辑表达式】
//【多重逻辑表达式递归】 》 $
void adv_logic_sym();
//【高级逻辑运算符】 》 &&
//【高级逻辑运算符】 》 ||
void logic_exp_recur();
//【逻辑表达式递归】 》 【逻辑运算符】 【逻辑表达式】
//【逻辑表达式递归】 》 $
void logic_exp();
//【逻辑表达式】 》 【表达式】 【逻辑表达式递归】
void logic_sym();
//【逻辑运算符】 》 <
//【逻辑运算符】 》 >
//【逻辑运算符】 》 ==
//【逻辑运算符】 》 !=
//【逻辑运算符】 》 >=
//【逻辑运算符】 》 <=
void suffix_exp();
//【后缀表达式】 》 【变量】 【后缀运算符】
void suffix_sym();
//【后缀运算符】 》 ++
//【后缀运算符】 》 --
void if_sentence();
//【条件语句】 》 if ( 【多重逻辑表达式】 ) { 【函数块】 } 【否则语句】
void else_sentence();
//【否则语句】 》 else { 【函数块】 }
//【否则语句】 》 $
void func_return();
//【函数返回】 》 return 【因式】 ;
void scan_sentence();
//【读语句】 》 scan(【标志符】)
void print_sentence();
//【写语句】 》 print( 【字符串】 )|print(【变量】)
void Panic(std::string info = "");

#endif
