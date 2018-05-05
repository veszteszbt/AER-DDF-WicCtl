// Generated by Bisonc++ V6.00.00 on Sat, 05 May 2018 11:30:01 +0200

// hdr/includes
#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <exception>
#include <vector>
#include <iostream>
// $insert preincludes
#include "semantics.h"

// hdr/baseclass

namespace // anonymous
{
    struct PI__;
}



class ParserBase
{
    public:
        enum DebugMode__
        {
            OFF           = 0,
            ON            = 1 << 0,
            ACTIONCASES   = 1 << 1
        };

// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        KEYWORD_IF = 257,
        KEYWORD_THEN,
        KEYWORD_ELSE,
        KEYWORD_ELIF,
        KEYWORD_FI,
        KEYWORD_CASE,
        KEYWORD_IN,
        KEYWORD_ESAC,
        KEYWORD_FOR,
        KEYWORD_WHILE,
        KEYWORD_UNTIL,
        KEYWORD_DO,
        KEYWORD_DONE,
        OCURLY,
        CCURLY,
        PIPE_SYMBOL,
        ANDF_SYMBOL,
        ORF_SYMBOL,
        COMMAND_SEPARATOR,
        CASE_DELIMITER,
        BACKGROUND_COMMANDS,
        OPARENTHESIS,
        CPARENTHESIS,
        INPUT_REDIRECTION,
        INPUT_FROM_A_HERE_DOCUMENT,
        OUTPUT_CREATION,
        OUTPUT_APPEND,
        SINGLEQUOTE,
        DOUBLEQUOTE,
        DOUBLE,
        INTEGER,
        IDENTIFIER,
        NEGATE,
        HEXADECIMAL,
        CONST_TRUE,
        CONST_FALSE,
        CONST_PI,
        OPERATOR_LET_BE,
        OPERATOR_AND,
        OPERATOR_OR,
        OPERATOR_EQUAL,
        OPERATOR_GREATER_THAN,
        OPERATOR_LESS_THAN,
        OPERATOR_GREATER_EQUAL,
        OPERATOR_LESS_EQUAL,
        OPERATOR_NOT_EQUAL,
        OPERATOR_PLUS,
        OPERATOR_MINUS,
        OPERATOR_MULTIPLICATION,
        OPERATOR_DIVISION,
        OPERATOR_MODULO,
        OPERATOR_POWER,
        UNARY_MINUS,
    };

// $insert LTYPE
    struct LTYPE__
    {
        int timestamp;
        int first_line;
        int first_column;
        int last_line;
        int last_column;
        char *text;
    };
    
// $insert STYPE
union STYPE__
{
 std::string *str;
 int *integ;
 double *dbl;
 expression_desc *exd;
 command_list_desc *cld;
 command_desc *cd;
};


    private:
                        // state  semval
        typedef std::pair<size_t, STYPE__> StatePair;
                       // token   semval
        typedef std::pair<int,    STYPE__> TokenPair;

        int d_stackIdx = -1;
        std::vector<StatePair> d_stateStack;
        StatePair  *d_vsp = 0;       // points to the topmost value stack
        size_t      d_state = 0;

        TokenPair   d_next;
        int         d_token;

        bool        d_terminalToken = false;
        bool        d_recovery = false;

// $insert LTYPEstack
        std::vector<LTYPE__>      d_locationStack;
        LTYPE__  *d_lsp;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            UNEXPECTED_TOKEN__,
        };

        bool        d_actionCases__ = false;    // set by options/directives
        bool        d_debug__ = true;
        size_t      d_requiredTokens__;
        size_t      d_nErrors__;                // initialized by clearin()
        size_t      d_acceptedTokens__;
        STYPE__     d_val__;

// $insert LTYPEdata
        LTYPE__   d_loc__;
        
        LTYPE__  const &lsp__(int idx) const
        {
            return *(d_lsp + idx);
        }
        

        ParserBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;

        STYPE__ &vs__(int idx);             // value stack element idx 
        int  lookup__() const;
        int  savedToken__() const;
        int  token__() const;
        size_t stackSize__() const;
        size_t state__() const;
        size_t top__() const;
        void clearin__();
        void errorVerbose__();
        void lex__(int token);
        void popToken__();
        void pop__(size_t count = 1);
        void pushToken__(int token);
        void push__(size_t nextState);
        void redoToken__();
        bool recovery__() const;
        void reduce__(int rule);
        void shift__(int state);
        void startRecovery__();

    public:
        void setDebug(bool mode);
        void setDebug(DebugMode__ mode);
}; 

// hdr/abort
inline void ParserBase::ABORT() const
{
    throw PARSE_ABORT__;
}

// hdr/accept
inline void ParserBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}


// hdr/error
inline void ParserBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}

// hdr/savedtoken
inline int ParserBase::savedToken__() const
{
    return d_next.first;
}

// hdr/opbitand
inline ParserBase::DebugMode__ operator&(ParserBase::DebugMode__ lhs,
                                     ParserBase::DebugMode__ rhs)
{
    return static_cast<ParserBase::DebugMode__>(
            static_cast<int>(lhs) & rhs);
}

// hdr/opbitor
inline ParserBase::DebugMode__ operator|(ParserBase::DebugMode__ lhs, 
                                     ParserBase::DebugMode__ rhs)
{
    return static_cast<ParserBase::DebugMode__>(static_cast<int>(lhs) | rhs);
};

// hdr/recovery
inline bool ParserBase::recovery__() const
{
    return d_recovery;
}

// hdr/stacksize
inline size_t ParserBase::stackSize__() const
{
    return d_stackIdx + 1;
}

// hdr/state
inline size_t ParserBase::state__() const
{
    return d_state;
}

// hdr/token
inline int ParserBase::token__() const
{
    return d_token;
}

// hdr/vs
inline ParserBase::STYPE__ &ParserBase::vs__(int idx) 
{
    return (d_vsp + idx)->second;
}

// hdr/tail
// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif



