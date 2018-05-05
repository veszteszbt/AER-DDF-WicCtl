CXX=g++
CXXFLAGS= -std=c++17 -Wall -g3 -pthread -I.
SDIR=scanner
PDIR=parser
JDIR=journal
FDEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h
BDEPS=$(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h
SDEPS=$(PDIR)/semantics.h
JDEPS=$(JDIR)/journal.h
DEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h $(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h $(PDIR)/semantics.h
OBJ=main.o lex.o parse.o semantics.o journal.o

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

journal.o: $(JDIR)/journal.cc $(JDEPS)
	$(CXX) $(CXXFLAGS) -I$(JDIR) -c $(JDIR)/journal.cc


.PHONY: clean flex bison test

clean:
	rm -f $(OBJ)

flex:
	./flexbuild
bison:
	./bisonbuild
test:
	./test/test.sh
