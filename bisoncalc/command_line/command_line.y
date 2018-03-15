%baseclass-preinclude <iostream>
%lsp-needed


%union
{
    int u_hex;
    long double u_num;
    std::string u_wor;
    std::string u_nam;
}

%token FOR
%token DO
%token DONE
%token WHILE
%token IN
%token UNTIL
%token CASE
%token ESAC
%token IF
%token THEN
%token FI
%token ELIF
%token ELSE
%token OPARENTHESES
%token CPARENTHESES
%token OCURLY
%token CCURLY
%token WORD
%token NAME
%token NUMBER
%token ET
%token SEMICOLON
%token DOUBLESEMICOLON
%token AND
%token OR
%token PIPE
%token ASSIGN
%token SINGLEQUOTE
%token DOUBLEQUOTE
%token HEXADECIMAL


%start command


%%





item:
    WORD
    {
        std::cout << "item->WORD" << std::endl;
    }
|
    NAME ASSIGN value
    {
        std::cout << "item->NAME ASSIGN WORD" << std::endl;
    }
;

value:
    WORD
    {
        std::cout << "value->WORD" << std::endl;
    }
|
    SINGLEQUOTE
    {
        std::cout << "value->SINGLEQUOTE" << std::endl;
    }
|
    DOUBLEQUOTE
    {
        std::cout << "value->DOUBLEQUOTE" << std::endl;
    }
|
    HEXADECIMAL
    {
        std::cout << "value->HEXADECIMAL" << std::endl;
    }
|
    NUMBER
    {
        std::cout << "value->NUMBER" << std::endl;
    }
|
    NAME
    {
        std::cout << "value -> NAME" << std::endl;
    }
;


simplecommand:
    item
    {
        std::cout << "simplecommand -> item" << std::endl;
    }
|
    simplecommand item
    {
        std::cout << "simplecommand -> simple-command item" << std::endl;
    }
;

command:
    simplecommand
    {
        std::cout << "command -> simplecommand" << std::endl;
    }
|
    OPARENTHESES commandlist CPARENTHESES
    {
        std::cout << "command -> OPARENTHESES commandlist CPARENTHESES" << std::endl;
    }
|
    OCURLY commandlist CCURLY
    {
        std::cout << "command -> OCURLY commandlist CCURLY" << std::endl;
    }
|
    FOR NAME IN wordholder DO commandlist DONE
    {
        std::cout << "command -> FOR NAME IN wordholder DO commandlist DONE" << std::endl;
    }
|
    WHILE commandlist DO commandlist DONE
    {
        std::cout << "command -> WHILE commandlist DO commandlist DONE" << std::endl;
    }
|
    UNTIL commandlist DO commandlist DONE
    {
        std::cout << "command -> UNTIL commandlist DO commandlist DONE" << std::endl;
    }
|
    CASE WORD IN casepartholder ESAC
    {
        std::cout << "command -> CASE WORD IN casepartholder ESAC" << std::endl;
    }
|
    IF commandlist THEN commandlist elsepart FI
    {
        std::cout << "command -> IF commandlist THEN commandlist elsepart FI" << std::endl;
    }
;

wordholder:
    value
    {
        std::cout << "wordholder -> WORD" << std::endl;
    }
|
    wordholder value
    {
        std::cout << "wordholder -> wordholder WORD" << std::endl;
    }
;

casepartholder:
    casepart
    {
        std::cout << "casepartholder -> casepart" << std::endl;
    }
|
    casepartholder casepart
    {
        std::cout << "casepartholder -> casepartholder casepart" << std::endl;
    }
;

pipeline:
    command
    {
        std::cout << "pipeline -> command" << std::endl;
    }
;

andor:
    pipeline
    {
        std::cout << "andor -> pipeline" << std::endl;
    }
|
    andor AND pipeline
    {
        std::cout << "andor -> andor AND pipeline" << std::endl;
    }
|
    andor OR pipeline
    {
        std::cout << "andor -> andor OR pipeline" << std::endl;
    }
;

commandlist:
    andor
    {
        std::cout << "commandlist -> andor" << std::endl;
    }
    commandlist SEMICOLON
    {
        std::cout << "commandlist -> commandlist SEMICOLON" << std::endl;
    }
|
    commandlist SEMICOLON andor
    {
        std::cout << "commandlist -> commandlist SEMICOLON andor" << std::endl;
    }
;

casepart:
    pattern CPARENTHESES commandlist DOUBLESEMICOLON
    {
        std::cout << "casepart -> pattern CPARENTHESES commandlist DOUBLESEMICOLON" << std::endl;
    }
;

pattern:
    WORD
    {
        std::cout << "pattern -> WORD" << std::endl;
    }
    pattern PIPE WORD
    {
        std::cout << "pattern -> pattern PIPE WORD" << std::endl;
    }
;

elsepart:
    ELIF commandlist THEN commandlist elsepart
    {
        std::cout << "elsepart -> ELIF commandlist THEN commandlist elsepart" << std::endl;
    }
|
    ELSE commandlist
    {
        std::cout << "elsepart -> ELSE commandlist" << std::endl;
    }
|
    empty
    {
        std::cout << "elsepart -> empty" << std::endl;
    }
;

empty:
    //empty
    {
        std::cout << "empty" << std::endl;
    }
;

