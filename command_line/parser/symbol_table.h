#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <vector>
#include <map>
#include <unordered_map>
#include <journal.h>
//#include "../journal/journal.h"
#include <iostream>
#include <string>
#include <cmath>
// #include <ios>
#include <sstream>
#include <list>
#include <cstdlib>
#include <cerrno>
// #include <algorithm>
#include "../types/meta.hh"

class var_value;

typedef std::map<std::string, var_value> arraypair;

void delete_from_arraypair(arraypair &a, const std::string &k);

enum type
{
	u_integer,
	u_double,
	u_string,
	u_array,
	u_null,
	// u_date
};

class var_value
{
	friend class get_min;
	friend class get_max;

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
		~value(){}; // TODO ezt később fix

		/*template<typename T>
		void set_value(T);*/
	} val;

	template <typename Titerator>
	int get_boundary_value_key_impl(const Titerator begin, const Titerator end);

	int getMaxKey();
	int getMinKey();

	template <typename Ttype>
	std::enable_if_t< types::meta::is_one_of_v<Ttype, int, double>, void >
	assign_impl(const type &t, var_value right);

	void unio(const arraypair& b);

	template <typename Top>
	void insert_with_impl(const std::string &s, const var_value &a);

	template <typename Op>
	void insert_impl(const var_value &a);

public:
	var_value(int i);
	var_value(double d);
	var_value(std::string* s);
	var_value(arraypair* a);
	var_value(const var_value& other);
	var_value();
	~var_value();

	//void delete_element_with_key(std::string key);
	//void delete_elements_with_key(std::vector<std::string> vec);

	int get_size();
	type get_type() const;
	var_value return_element_with_key(var_value v);
	std::vector<var_value> return_array_elements(); // lehet nem kell

	void set_type_noconvert(type t);

	void insert(std::string s, const var_value &a);
	void insert(const var_value &a);
	void insert_after_max(const var_value &a);
	void insert_before_min(const var_value &a);
	void insert_with_add(const std::string &s, const var_value &a);
	void insert_with_dif(const std::string &s, const var_value &a);
	void insert_with_overwrite(const std::string &s, var_value a);

	std::pair<bool, arraypair::iterator> exists_in_array(std::string s);
	std::string find_first_element_having_value(var_value v);
	std::string find_last_element_having_value(var_value v);
	std::vector<std::string> find_elements_having_value(var_value v);

	//template<typename T>
	//void convert_to_type()
	//void set_value(std::unordered_map<std::string, var_value> a);

	bool value(int&) const;
	bool value(bool&) const;
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

template <typename Top>
void var_value::insert_with_impl(const std::string &s, const var_value &a)
{
	if (var_type != u_array)
	{ std::cerr << "can't insert since its not an array!" << std::endl; }
	else
	{
		bool exists;
		arraypair::iterator it;
		std::tie(exists, it) = exists_in_array(s);

		if (exists)
			it->second = Top().calculate(it->second, a);
		else
			insert(s, a);
	}
}

template <typename Titerator>
int var_value::get_boundary_value_key_impl(const Titerator begin, const Titerator end)
{
	int boundary = -1;
	if (get_type() != u_array)
		std::cerr << "cant get boundary element from a non array" << std::endl;

	else
	{
		for (auto it = begin; it != end; ++it)
		{
			int temperrno = errno;
			errno = 0;
			char * eptr;
			long int temp = strtol(it->first.c_str(), &eptr, 10);
			if(!errno && !*eptr)
			{
				int currval = static_cast<int>(temp);
				if(static_cast<long int>(currval) == temp)
					return currval;
			}
			errno = errno + temperrno;
		}
	}
	return boundary;
}

struct variable_desc
{
	int decl_row;
	var_value value;

	variable_desc(); // kell a map-hez
	variable_desc(const variable_desc& other);
	variable_desc(int row_number, var_value v);

	var_value return_value();

	variable_desc& operator=(variable_desc right);
};

class Symbol_Table
{
private:
	std::vector<std::unordered_map<std::string, variable_desc> > symbol_table;

public:
	Symbol_Table();

	variable_desc get_value(std::string* name);

	void set_value(std::string* name, variable_desc v);
	void set_local_value(std::string* name, variable_desc v);
	void set_default_value(std::string name, var_value v);

	int find_variable(std::string* name);

	void increase_stack();
	void decrease_stack();
};

#endif
