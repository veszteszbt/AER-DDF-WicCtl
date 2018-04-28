CXX=g++
CXXFLAGS= -std=c++17 -Wall -g3
SDIR=scanner
PDIR=parser
FDEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h
BDEPS=$(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h
SDEPS=$(PDIR)/semantics.h
DEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h $(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h $(PDIR)/semantics.h
OBJ=main.o lex.o parse.o semantics.o

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o commandline $(OBJ)

main.o: main.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c main.cc

lex.o: $(SDIR)/lex.cc $(FDEPS)
	$(CXX) $(CXXFLAGS) -c $(SDIR)/lex.cc

parse.o: $(PDIR)/parse.cc $(BDEPS)
	$(CXX) $(CXXFLAGS) -c $(PDIR)/parse.cc

semantics.o: $(PDIR)/semantics.cc $(SDEPS)
	$(CXX) $(CXXFLAGS) -c $(PDIR)/semantics.cc

.PHONY: clean flex bison

clean:
	rm -f $(OBJ)

flex:
	./flexbuild
bison:
	./bisonbuild
