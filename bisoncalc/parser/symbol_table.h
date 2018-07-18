#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <vector>
#include <map>
#include <unordered_map>
#include <journal/journal.h>
#include <iostream>
#include <string>
#include <cmath>
//#include <ios>
#include <sstream>
#include <list>
#include <cstdlib>
#include <cerrno>
//#include <algorithm>
#include "../types/meta.hh"

class var_value;

// typedef std::pair<std::unordered_map<std::string, var_value>, std::list<std::string> > arraypair;
typedef std::map<std::string, var_value> arraypair;



void delete_from_arraypair(arraypair &a, std::string k);

enum type{ 
	u_integer,
	u_double,
	u_string,
	u_array,
	u_null,
	//u_date
	};

class var_value
{
	type var_type;

	union value{
		int intval;
		double doubleval;
		std::string* stringval;
		arraypair* array;

		value(int i) : intval(i) {}
		value(double d) : doubleval(d) {}
		value(std::string* s) : stringval(s) {}
		value(arraypair* a) : array(a) {}

		value() : intval(0){}
		~value(){}; //TODO ezt később fix

		/*template<typename T>
		void set_value(T);*/
	} val;

public:
	var_value(int i);
	var_value(double d);
	var_value(std::string* s);
	var_value(arraypair* a);
	var_value(const var_value& other);
	var_value();
	~var_value();

	type get_type() const;
	void set_type_noconvert(type t);

	bool exists_in_array(std::string s);
	//std::unordered_map<std::string, var_value>::iterator find(std::string s);
	//void add_to_element(std::unordered_map<std::string, var_value>::iterator it);
	std::string find_first_element_having_value(var_value v);
	std::string find_last_element_having_value(var_value v);
	std::vector<std::string> find_elements_having_value(var_value v);
	std::vector<var_value> return_array_elements(); // lehet nem kell
	//void delete_element_with_key(std::string key);
	//void delete_elements_with_key(std::vector<std::string> vec);
	int get_size();
	void insert(std::string s, var_value a);
	void insert(var_value a);
	void insert_after_max(var_value a);
	void insert_before_min(var_value a);
	void insert_with_add(std::string s, var_value a);
	void insert_with_dif(std::string s, var_value a);
	void insert_with_overwrite(std::string s, var_value a);
	var_value return_element_with_key(var_value v);
	int getMaxKey();
	int getMinKey();


	//template<typename T>
	//void convert_to_type()
	//void set_value(std::unordered_map<std::string, var_value> a);

	bool value(int&) const;
	bool value(double&) const;
	bool value(std::string&) const;
	bool value(arraypair&) const;

	void set_value(int);
	void set_value(double);
	void set_value(std::string&);
	void set_value(std::string*);
	void set_value(arraypair*);

	void append(std::string s);
	//void add(var_value v);
	var_value& operator=(var_value right);

	friend var_value operator+(var_value l, var_value r);
	friend var_value operator-(var_value l, var_value r);
	friend var_value operator*(var_value l, var_value r);
	friend var_value operator/(var_value l, var_value r);
	friend var_value operator^(var_value l, var_value r);
	friend var_value operator%(var_value l, var_value r);
	//friend var_value operator++(var_value o);
	friend int operator==(var_value l, var_value r);
	friend int operator!=(var_value l, var_value r);
	friend int operator<(var_value l, var_value r);
	friend int operator>(var_value l, var_value r);
	friend int operator>=(var_value l, var_value r);
	friend int operator<=(var_value l, var_value r);
	//friend int* operator*()(var_value v);
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
	void set_default_value(std::string name, var_value v);
	variable_desc get_value(std::string* name);
	void increase_stack();
	void decrease_stack();

	private:
		std::vector<std::unordered_map<std::string, variable_desc> > symbol_table;
};

#endif