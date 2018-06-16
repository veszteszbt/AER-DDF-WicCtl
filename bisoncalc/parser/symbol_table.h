#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <vector>
#include <map>
#include <journal/journal.h>
#include <iostream>

enum type{ u_integer, u_double, u_string };

struct variable_desc
{
	variable_desc(int row_number, type data_type, int value) : decl_row(row_number), var_type(data_type), intval(value) {}
	variable_desc(){} //kell a maphoz

	int decl_row;
	type var_type;
	/*union value{
		int intval;
		double doubleval;
		std::string strval;
	};*/
	int intval;
};

class Symbol_Table
{
	public:
	Symbol_Table();

	int find_variable(std::string* name);
	void set_value(std::string* name, variable_desc v);
	variable_desc get_value(std::string* name);
	void increase_stack();
	void decrease_stack();

	private:
		std::vector<std::map<std::string, variable_desc> > symbol_table;
};

#endif