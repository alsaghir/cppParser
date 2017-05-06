# c++ Parser
Recursive descent parser using c++

<b>The language context free rules are</b>
```
Program --> Statement_list  
Statement_list --> Statement_list Statement | Statement  
Statement --> Var_statement | If_statement  
Var_statement --> (int|void)ID | (int|void)ID[num];  
If_statement --> if (Expression) Statement_list | if (Expression) Statement_list else Statement_list  
Expression --> Var=Expression  
Var --> ID|ID[num]  
Expression --> add-expression Relop add-expression | add-expression  
Relop --> >=,<=,<>,>,<,==  
add-expression --> add-expression addop term | term  
addop --> +|-  
term --> term mulop factor | factor  
mulop --> *|/  
factor --> num  
```
> **ID, num are terminal classes. The rest (int, void, else, <=, =..etc) of terminals are lexemes.**

#### To be able to work using recursive descent, modified rules presented
```
Program --> Statement_list  
Statement_list --> Statement Statement_list_dash  
Statement_list_dash --> Statement Statement_list_dash | ε  
Statement --> Var_statement | If_statement  
Var_statement --> ( IV ) Var  
IV --> int | void  
Var --> id | id[num];  
If_statement --> if (Expression) Statement_list else Statement_list | if (Expression) Statement_list  
Expression --> Var=Expression | add-expression Relop add-expression | add-expression     
Relop --> >= | <= | <> | > | < | ==  
add-expression --> term add-expression_dash  
add-expression_dash --> addop term add-expression_dash | ε  
addop --> +|-  
term --> factor term_dash  
term_dash --> mulop factor term_dash | ε  
mulop --> *|/  
factor --> num  
```
#### Input are tokens in specific format

Take a look to Sample.hamada for example and here are some examples. These examples should be valid according to the language and produce success on parsing.

Example 1:
```
<kw, if>
<oc, (>
<num, 4>
<eq, ==>
<num, 3>
<cc, )>
<oc, (>
<kw, int>
<cc, )>
<id, aa>
<os, [>
<num, 66>
<cs, ]>
<kw, else>
<oc, (>
<kw, void>
<cc, )>
<id, bb>
```

Example 2:
```
<oc, (>
<kw, int>
<cc, )>
<id, bb>
<os, [>
<num, 66>
<cs, ]>
<semi, ;>
```

#### More output

light-output.cpp & extensiveOutput.cpp are completely commented but saved for sake of testing ONLY. They have to much outputs on each function calling and more.