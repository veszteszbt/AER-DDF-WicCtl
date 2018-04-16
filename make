#!/bin/bash

program=`pwd`
program=`basename $program`

case $1 in
    (flex)
        read -p "WARNING: This operation will delete your current flex++ files! Press \"y\" to continue. Or press \"i\" to prevent auto inserting and generate clean.
" answer
        case $answer in
        ("i")
            cd scanner
            echo "rm -f lex.cc Scanner.ih Scanner.h Scannerbase.h"
            rm -f lex.cc Scanner.ih Scanner.h Scannerbase.h
            echo "flexc++ lexer"
            flexc++ lexer
            cd ..
        ;;
        ("y")
            cd scanner
            echo "rm -f lex.cc Scanner.ih Scanner.h Scannerbase.h"
            rm -f lex.cc Scanner.ih Scanner.h Scannerbase.h
            echo "flexc++ lexer"
            flexc++ lexer

            echo "inserting into Scanner.h"
            sed -i 's/#include "Scannerbase.h"/#include "Scannerbase.h"\n#include "..\/parser\/Parserbase.h"/' Scanner.h
            sed -i 's/Scanner(std::string const &infile, std::string const &outfile);/Scanner(std::string const \&infile, std::ostream \&out);\n\t\tScanner(std::string const \&infile, std::string const \&outfile);/' Scanner.h
            sed -i 's/inline Scanner::Scanner(std::string const &infile, std::string const &outfile)/inline Scanner::Scanner(std::string const \&infile, std::ostream \&out)\n:\n\tScannerBase(infile, out)\n{}\n\ninline Scanner::Scanner(std::string const \&infile, std::string const \&outfile)/' Scanner.h

            echo "insering into Scannerbase.h"
            sed -i 's/ScannerBase(std::string const &infilename, std::string const &outfilename);/ScannerBase(std::string const \&infilename, std::string const \&outfilename);\n\tScannerBase(std::string const \&infilename, std::ostream \&out);/' Scannerbase.h

            echo "inserting into lex.cc"
            sed -i 's/void ScannerBase::switchStream__(std::istream &in, size_t lineNr)/ScannerBase::ScannerBase(std::string const \&infilename, std::ostream \&out)\n:\n\td_filename(infilename),\n\td_out(new std::ostream(out.rdbuf())),\n\td_input(new std::ifstream(infilename)),\n\td_dfaBase__(s_dfa__)\n{}\n\nvoid ScannerBase::switchStream__(std::istream \&in, size_t lineNr)/' lex.cc
            cd ..
        ;;
        (*)
            echo "Operation aborted."
        ;;
        esac
    ;;
    (bison)
        read -p "WARNING: This operation will delete your current bisonc++ files! Press \"y\" to continue. Or press \"i\" to prevent auto inserting and generate clean.
" answer
        case $answer in
        ("i")
            cd parser
            echo "rm -f Parser.h Parserbase.h parse.cc Parser.ih"
            rm -f Parser.h Parserbase.h parse.cc Parser.ih
            echo "bisonc++ grammar"
            bisonc++ grammar
            cd ..
    ;;
        ("y")
            cd parser
            echo "rm -f Parser.h Parserbase.h parse.cc Parser.ih"
            rm -f Parser.h Parserbase.h parse.cc Parser.ih
            echo "bisonc++ grammar"
            bisonc++ grammar

            echo "insering into Parser.h"
            sed -i 's/Parser() = default;/Parser() = default;\n\t\tParser(std::string inFile) : d_scanner(inFile, std::cout){}/' Parser.h
            sed -i 's/private:/private:\n\t\tstd::map<std::string, int> symbol_table;/' Parser.h

            echo "insering into Parser.ih"
            sed -i 's/std::cerr << "Syntax error\\n";/std::cerr << d_loc__.first_line << " :Syntax error\\n";/' Parser.ih
            sed -i 's/return d_scanner.lex();/int ret = d_scanner.lex();\n\td_loc__.first_line = d_scanner.lineNr();\n\tif( ret == IDENTIFIER )\n\t{\n\t\td_val__.str = new std::string(d_scanner.matched());\n\t}\n\treturn ret;/' Parser.ih
            cd ..
        ;;
        (*)
            echo "Operation aborted."
        ;;
        esac
    ;;
    (build)
        echo "g++ --std=c++17 -Wall -o commandline main.cc parser/parse.cc scanner/lex.cc"
        g++ --std=c++17 -g3 -Wall -o commandline main.cc parser/parse.cc scanner/lex.cc
    ;;
    (*)
        echo "use
\"./make bison\" for grammar reset
\"./make flex\" for lexer reset
\"./make build\" for build"
    ;;
esac
