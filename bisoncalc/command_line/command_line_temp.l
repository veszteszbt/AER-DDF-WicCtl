%option noyywrap c++ yylineno


%{
#include <iostream>
#include <cstdlib>
#include "bisoncpp-master/bisonc++/parser/parserbase.h"
%}

WS  [ \n\t\r\v]


%%

"for" std::cout << "FOR" ;
"do" std::cout << "DO" ;
"done" std::cout << "DONE" ;
"while" std::cout << "WHILE" ;
"in" std::cout << "IN" ;
"until" std::cout << "UNTIL" ;
"case" std::cout << "CASE" ;
"esac" std::cout << "ESAC" ;
"if" std::cout << "IF" ;
"fi" std::cout << "FI" ;
"then" std::cout << "THEN" ;
"elif" std::cout << "ELIF" ;
"else" std::cout << "ELSE" ;
"(" std::cout << "OPARENTHESES" ;
")" std::cout << "CPARENTHESES" ;
"{" std::cout << "OCURLY" ;
"}" std::cout << "CCURLY" ;
"&" std::cout << "ET" ;
";" std::cout << "SEMICOLON" ;
";;" std::cout << "DOUBLESEMICOLON" ;
"&&" std::cout << "AND" ;
"||" std::cout << "OR" ;
"|" std::cout << "PIPE" ;
"=" std::cout << "ASSIGN" ;


(\'[^']*\') std::cout << "SINGLEQUOTE" ;
(\"[^"]*\") std::cout << "DOUBLEQUOTE" ;
0x[0-9]* std::cout << "HEXADECIMAL" ;
[0-9]+(,[0-9]+)* std::cout << "NUMBER" ;
[a-zA-Z]([a-zA-Z0-9]|"_")* std::cout << "NAME" ;
([a-zA-Z0-9]|"_")+ std::cout << "WORD" ;


{WS}+ //whitespace

.   {
    //std::cerr << lineno() << ": Lexikalis hiba." << std::endl;
        std::cerr << "Lexical error." << std::endl;
        exit(1);
    }
%%

