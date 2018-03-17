#include "../parser/Parser.ih"
#include <fstream>
#include <iostream>
#include <cstdlib>



int main(int argc, char* argv[])
{
    std::string testfile = "syntax_test.txt";
    Parser testparser(testfile);
    //Parser testparser;
    testparser.parse();
}
