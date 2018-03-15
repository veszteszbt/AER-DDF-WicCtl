// Generated by Flexc++ V0.93.00 on Mon, 20 Feb 2012 13:48:09 +0100

#ifndef Scanner_H_INCLUDED_
#define Scanner_H_INCLUDED_

#include "../semval/semval.h"

// $insert baseclass_h
#include "scannerbase.h"


// $insert classHead
class Scanner: public ScannerBase
{
    SemVal *d_semval;

    public:
        Scanner(SemVal *semval);

        // $insert lexFunctionDecl
        int lex();

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts
        void postCode(PostEnum__);
};

inline void Scanner::postCode(PostEnum__)
{}


// $insert scannerConstructors
inline Scanner::Scanner(SemVal *semval)
:
    ScannerBase(std::cin, std::cout),
    d_semval(semval)
{}

// $insert inlineLexFunction
inline int Scanner::lex()
{
    return lex__();
}

inline void Scanner::preCode() 
{
    // optionally replace by your own code
}

inline void Scanner::print() 
{
    print__();
}


#endif // Scanner_H_INCLUDED_

