%option noyywrap c++ yylineno


%{
#include <iostream>
#include <cstdlib>
#include "bisoncpp-master/bisonc++/parser/parserbase.h"
%}

WS  [ \n\t\r\v]
UNDERSCORE "_"


%%

"for" return Parser::FOR;
"do" return Parser::DO;
"done" return Parser::DONE;
"while" return Parser::WHILE;
"in" return Parser::IN;
"until" return Parser::UNTIL;
"case" return Parser::CASE;
"esac" return Parser::ESAC;
"if" return Parser::IF;
"fi" return Parser::FI;
"then" return Parser::THEN;
"elif" return Parser::ELIF;
"else" return Parser::ELSE;
"(" return Parser::OPARENTHESES;
")" return Parser::CPARENTHESES;
"{" return Parser::OCURLY;
"}" return Parser::CCURLY;
"&" return Parser::ET;
";" return Parser::SEMICOLON;
";;" return Parser::DOUBLESEMICOLON;
"&&" return Parser::AND;
"||" return Parser::OR;
"|" return Parser::PIPE;
"=" return Parser::ASSIGN;


(\'[^']*\') return parser::SINGLEQUOTE;
(\"[^"]*\") return parser::DOUBLEQUOTE;
0x[0-9]* return parser::HEXADECIMAL;
[0-9]+(,[0-9]+)* return Parser::NUMBER;
[a-zA-Z]([a-zA-Z0-9]|UNDERSCORE)* return Parser::NAME;
([a-zA-Z0-9]|UNDERSCORE)+ return Parser::WORD;


{WS}+ //whitespace

.   {
    //std::cerr << lineno() << ": Lexikalis hiba." << std::endl;
        std::cerr << "Lexical error." << std::endl;
        exit(1);
    }
%%

