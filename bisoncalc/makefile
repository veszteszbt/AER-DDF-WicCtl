CXX=g++
CXXFLAGS= -std=c++17 -Wall -g3 -pthread -I.
SDIR=scanner
PDIR=parser
JDIR=journal
FDEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h
BDEPS=$(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h
SDEPS=$(PDIR)/semantics.h
STABLEDEPS=$(PDIR)/symbol_table.h
JDEPS=$(JDIR)/journal.h
DEPS=$(SDIR)/Scanner.h $(SDIR)/Scanner.ih $(SDIR)/Scannerbase.h $(PDIR)/Parser.h $(PDIR)/Parser.ih $(PDIR)/Parserbase.h $(PDIR)/semantics.h
FNCTDEPS=functions.h $(SDEPS)
OBJ=main.o lex.o parse.o semantics.o symbol_table.o journal.o functions.o type.o

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

symbol_table.o: $(PDIR)/symbol_table.cc $(STABLEDEPS)
	$(CXX) $(CXXFLAGS) -c $(PDIR)/symbol_table.cc

journal.o: $(JDIR)/journal.cc $(JDEPS)
	$(CXX) $(CXXFLAGS) -I$(JDIR) -c $(JDIR)/journal.cc

functions.o: functions.cc $(FNCTDEPS)
	$(CXX) $(CXXFLAGS) -c functions.cc

type.o: types/type.cc types/type.h
	$(CXX) $(CXXFLAGS) -c types/type.cc

.PHONY: clean flex bison test

clean:
	rm -f $(OBJ)

flex:
	./flexbuild
bison:
	./bisonbuild
test:
	./test/test.sh
