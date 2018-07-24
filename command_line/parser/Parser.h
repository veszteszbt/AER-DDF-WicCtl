// Generated by Bisonc++ V6.00.00 on Tue, 24 Jul 2018 17:19:58 +0200

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
#include <sstream>


class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        Parser(){ParserBase::clearin__();}
		Parser(std::stringstream &ss) : d_scanner(ss, std::cout) { ParserBase::clearin__(); }
		Parser(std::string inFile) : d_scanner(inFile, std::cout){ ParserBase::clearin__(); }
        int parse();

    	Symbol_Table symbol_table;

	void process_this(std::stringstream &ss)
	{
		 std::cout << ss.str() << std::endl;
		d_scanner.switchIstream(ss);
		parse();
	}

	void process_this(const std::string &filename)
	{
		d_scanner.switchIstream(filename);
		parse();
	}

	void process_this()
	{
		d_scanner.switchIstream(std::cin);
		std::cout << "\n> program taking input from cin now:" << std::endl;
		parse();
	}

private:
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
