#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <vector>
#include <map>
#include <journal/journal.h>
#include <iostream>
#include <string>
#include <cmath>
//#include <ios>
//#include <sstream>
//#include <algorithm>

enum type{ u_integer, u_double, u_string };

class var_value
{
	type var_type;

	union value{
		int intval;
		double doubleval;
		std::string* stringval;

		value(int i) : intval(i) {}
		value(double d) : doubleval(d) {}
		value(std::string* s) : stringval(s) {}

		value() : intval(0){}
		~value(){}; //TODO ezt később fix

		/*template<typename T>
		void set_value(T);*/
	} val;

public:
	var_value(int i);
	var_value(double d);
	var_value(std::string* s);
	var_value(const var_value& other);
	var_value();
	~var_value();

	type get_type() const;
	void set_type_noconvert(type t);
	void set_value(int i);
	void set_value(double d);
	void set_value(std::string s);

	template<typename T>
	T value() const;

	template<typename T>
	void set_value(T);

	void append(std::string s);
	var_value& operator=(var_value right);
	friend var_value operator+(var_value l, var_value r);
	friend var_value operator-(var_value l, var_value r);
	friend var_value operator*(var_value l, var_value r);
	friend var_value operator/(var_value l, var_value r);
	friend var_value operator^(var_value l, var_value r);
	friend var_value operator%(var_value l, var_value r);
	friend int operator==(var_value l, var_value r);
	friend int operator!=(var_value l, var_value r);
	friend int operator<(var_value l, var_value r);
	friend int operator>(var_value l, var_value r);
	friend int operator>=(var_value l, var_value r);
	friend int operator<=(var_value l, var_value r);
	friend std::ostream& operator<<(std::ostream& out, var_value &v);
	//friend std::istream& operator>>(std::istream& in, var_value &v);
};

struct variable_desc
{
	variable_desc(int row_number, var_value v) : decl_row(row_number), value(v) {}
	variable_desc(const variable_desc& other);
	variable_desc(){} //kell a maphoz

	int decl_row;
	var_value value;
	
	var_value return_value();

	variable_desc& operator=(variable_desc right);
};

class Symbol_Table
{
	public:
	Symbol_Table();

	int find_variable(std::string* name);
	void set_value(std::string* name, variable_desc v);
	void set_local_value(std::string* name, variable_desc v);
	variable_desc get_value(std::string* name);
	void increase_stack();
	void decrease_stack();

	private:
		std::vector<std::map<std::string, variable_desc> > symbol_table;
};

#endif