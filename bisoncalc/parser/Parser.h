// Generated by Bisonc++ V6.00.00 on Tue, 10 Jul 2018 16:18:07 +0200

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
// $insert scanner.h
#include "../scanner/Scanner.h"


#undef Parser
    // CAVEAT: between the baseclass-include directive and the 
    // #undef directive in the previous line references to Parser 
    // are read as ParserBase.
    // If you need to include additional headers in this file 
    // you should do so after these comment-lines.
#include "symbol_table.h"


class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        Parser() = default;
		Parser(std::string inFile) : d_scanner(inFile, std::cout){}
        int parse();
		void finish(int i);

    	Symbol_Table symbol_table;

private:
		bool finished;
		int returnState;
        void error();                   // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc
        void exceptionHandler(std::exception const &exc);

    // support functions for parse():
        void executeAction__(int ruleNr);
        void errorRecovery__();
        void nextCycle__();
        void nextToken__();
        void print__();
};


#endif
