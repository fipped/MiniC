# MiniC 编译器
这是我们在 doraHack 上用 C++ 编写的一个 miniC 编译器。 

## 标记（Token）
- keywords = `if`|`else`|`while`|`for`|`switch`|`case`|`deafult`|`break`|`return`|`void`|`int`|`char`|`scan`|`print`
- letter = a | ... | z | A | ... | Z 
- digit = 0 | ... | 9
- space = '\t',' ','\n'
- NUM = digit+
- ID = letter(letter|digit)*
- STRING = "最多 1024 个字符. `"` 可以被 `\` 转义."
- CHAR = '任何字符'
- PLUS = `+`
- MINUS = `-`
- DIV = `/`
- MULT = `*`
- MOD = `%`
- PLUS2 = `++`
- MINUS2 = `--`
- ASSIGN = `=`
- EQUAL = `==`
- GREATER = `>`
- GREATEREQUAL = `>=`
- LESS = `<`
- LESSEQUAL = `<=`
- NOTEQUAL = `!=`
- LBRAC = `{`
- RBRAC = `}`
- LPAREN = `(`
- RPAREN = `)`
- LBRACE = `[`
- RBRACE = `]`
- COLON = `:`
- COMMA = `,`
- SEMICOLON = `;`
- END_OF_FILE = EOF

## 文法（Grammar）

_Program_           → _FunClosure_
_FunClosure_        → _Function_ _FunClosure_ | ε
_Function_          → _Type_ _Variable_(_ParameterDecl_){_FunBody_}
_Function_          → void _Variable_(_ParameterDecl_){_FunBody_}
_Type_              → int | char 
_Variable_          → ID
_Factor_            → (_Expression_)
_Factor_            → _VarOrFunCall_
_Factor_            → NUM | CHAR 
_VarOrFunCall_      → _Variable_ _FunSuffix_
_FunSuffix_         → (_VariableList_) | ε
_Expression_        → _FactorCombine_ _Term_ 

_FactorCombine_     → _Factor_ _FactorRecur_
_FactorRecur_     → * _Factor_ _FactorRecur_
_FactorRecur_     → / _Factor_ _FactorRecur_
_FactorRecur_     → % _Factor_ _FactorRecur_
_FactorRecur_     → ε

_Term_              → + _FactorCombine_ _Term_ 
_Term_              → - _FactorCombine_ _Term_ 
_Term_              → ε
_ParameterDecl_     → _Decl_ _DeclClosure_ | void | ε
_Decl_              → _Type_ _Variable_ _Assign_
_Assign_            → _RightVal_ | ε
_RightVal_          → _Expression_
_DeclClosure_       → , _Decl_ _DeclClosure_ | ε

_FunBody_           → _DeclStmtClosure_ _FunClosure_ 
_DeclStmtClosure_   → _DeclStmt_ _DeclStmtClosure_ | ε
_DeclStmt_          → _Decl_ ;

_FunClosure_        → _AssignStmt_ _FunClosure_
_FunClosure_        → _ForStmt_ _FunClosure_
_FunClosure_        → _Condition_ _FunClosure_
_FunClosure_        → _ReturnStmt_ _FunClosure_
_FunClosure_        → _ScanStmt_ _FunClosure_
_FunClosure_        → _PrintStmt_ _FunClosure_
_FunClosure_        → ε

_AssignStmt_        → _Variable_ _AssignOrFunCall_
_AssignOrFunCall_   → _RightVal_ ;
_AssignOrFunCall_   → (_ParameterList_) ;
_ParameterList_     → _Parameter_ _ParameterClosure_
_ParameterClosure_  → , _Parameter_ _ParameterClosure_
_ParameterClosure_  → ε
_Parameter_         → ID | NUM | CHAR 
_ForStmt_           → for (_AssignStmt_ _LogicStmt_; _SuffixStmt_){_FunctionBody_}

_MultLogicExpr_     → _LogiExpr_ _MultLogiExprRecur_
_MultLogiExprRecur_ → _AdvanLogiOp_ _MultLogicExpr_ | ε
_AdvanLogiOp_       → AND | OR 
_LogiExpr_          → _Expr_ _LogiExprRecur_
_LogiExprRecur_     → _LogicOp_ _LogiExpr_ | ε
_LogicOp_           → LESS | LESSEQUAL | NOTEQUAL | EQUAL | GREATER | GREATEREQUAL

_SuffixStmt_        → _Variable_ _SuffixOp_
_SuffixOp_          → PLUS2 | MINUS2
_IfStmt_            → IF ( _MultLogicExpr_ ) { _FunctionBody_ } _ElseStmt_
_ElseStmt_          → ELSE { _FunctionBody_ } | ε
_ReturnStmt_        → RETURN _Factor_ ;
_ScanStmt_          → SCAN ( _Variable_ ) ;
_PrintStmt_         → PRINT ( _Variable_ ) ; | PRINT ( STRING ) ;

## 模块（Modules）
### 词法分析器 Lexer
Lexer 读取字符，并组成符合要求的标记（Token）。

### 语法分析器 Paser
Paser 从 Lexer 中读取 Token ，并转换为中间表达式。