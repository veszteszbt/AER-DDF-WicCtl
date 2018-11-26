#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <journal.h>
//#include "../journal/journal.h"
#include "symbol_table.h"
//#include "../functions.h"



//generic expression class
struct expression_desc
{
	int row;
	var_value val;

	expression_desc(int row_number, var_value v);
	expression_desc(){}
	virtual ~expression_desc();

	int get_row();
	type get_type();
	void set_row(int &r);

	virtual var_value get_val() = 0;
	virtual void evaluate() = 0;
};

struct command_desc
{
	int row;

	command_desc();
	command_desc(int row_number);

	int get_row();
	virtual var_value get_return_value() = 0;

	void set_row(int &r);

	virtual void evaluate() = 0;
};

struct command_list_desc
{
	int row;
	std::vector<command_desc*> command_list;

	command_list_desc(command_list_desc* other);
	command_list_desc();

	int get_row();
	void evaluate();
	void add(command_desc* cd);
	void add(command_list_desc* other);
};

struct expr_binary : public expression_desc
{
	int row;
	type expr_type;
	expression_desc* l;
	expression_desc* r;

	expr_binary();
	expr_binary(int row_number, expression_desc* left, expression_desc* right);

	virtual var_value get_val() = 0;
};

struct expr_unary : public expression_desc
{
	int row;
	expression_desc* e;
	type expr_type;

	expr_unary();
	expr_unary(int row_number, expression_desc* ex);

	virtual var_value get_val() = 0;
};

//constant values
struct expr_const : public expression_desc
{
	int row;

	expr_const(int row_number, var_value v);
	expr_const(int row_number);

	void evaluate();
	type get_type();
	var_value get_val();
};

struct expr_callpar : public expression_desc
{
	int row;
	command_desc* nestedcall;

	expr_callpar(int row_number, command_desc* n);

	void evaluate();
	type get_type();
	var_value get_val();
};

//variables
struct expr_var : public expression_desc
{
	int row;
	std::string name;

	expr_var(int row_number, std::string var_name);

	void evaluate();
	type get_type();
	var_value get_val();
};

struct expr_arr : public expression_desc
{
	int row;
	int size;
	var_value val;

	expr_arr(int row_number, expr_arr* a);
	expr_arr(int row_number);

	int get_size();
	type get_type();
	var_value get_val();

	void evaluate();
	void deleteBecauseGccPolymorphicSucks();

	void add(expression_desc* e);
	void add(expression_desc* variable, expression_desc* varvalue);
};

struct assign : public command_desc
{
	int row;
	std::string* vname;
	expression_desc* e;

	assign(int row_number, std::string* var_name, expression_desc* ex);

	std::string get_name();
	var_value get_return_value();

	void evaluate();
};

// assignment for local variables (shadowing)
struct local_assign : public command_desc
{
	int row;
	std::string* vname;
	expression_desc* e;

	local_assign(int row_number, std::string* var_name, expression_desc* ex);

	std::string get_name();
	var_value get_return_value();

	void evaluate();
};

// expression list to store an array of expressions (for_in)
struct c_expression_list
{
	std::vector<expression_desc*> expr_list;

	c_expression_list();
	c_expression_list(c_expression_list* other);

	int get_size();

	void add(expression_desc* e);
	void add(c_expression_list* other);

	expression_desc* return_element(unsigned int i);
};

// paranthesis ()
struct expr_par : public expr_unary
{
	int row;
	expression_desc* e;

	expr_par(int row_number, expression_desc* nested);

	type get_type();
	var_value get_val();

	void evaluate();
};

// array element []
struct expr_ael : public expression_desc
{
	int row;
	std::string name;
	expression_desc* nth;

	expr_ael(int row_number, std::string var_name, expression_desc* n);

	var_value get_val();

	void evaluate();
};

// operator +
struct expr_add : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_add(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator -
struct expr_dif : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_dif(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator *
struct expr_mul : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_mul(int row_number, expression_desc* left, expression_desc* right);

	int get_row();			// TODO missing definition
	var_value get_val();

	void evaluate();
};

// operator /
struct expr_div : public expr_binary
{
	// int row; //???? ez kell ide?
	// > Attila says: Nem, mivel az ősosztályában van ilyen változó deklarálva
	expression_desc* l;
	expression_desc* r;

	expr_div(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator ^ (alternative **)
struct expr_pow : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_pow(int row_number, expression_desc* left, expression_desc* right);

	int get_row();			// TODO missing definition
	var_value get_val();

	void evaluate();
};

// operator %
struct expr_mod : public expr_binary
{
	// int row; // comment for the same reason
	expression_desc* l;
	expression_desc* r;

	expr_mod(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator -o
struct expr_or : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_or(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator -a
struct expr_and : public expr_binary
{
	expression_desc* l;
	expression_desc* r;

	expr_and(int row_number, expression_desc* left, expression_desc* right);

	type expr_type;

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator -eq (equals)
struct expr_eq : public expr_binary
{
	type expr_type;

	expression_desc* l;
	expression_desc* r;

	expr_eq(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// operator -neq (not equal)
struct expr_neq : public expr_binary
{
	type expr_type;

	expression_desc* l;
	expression_desc* r;

	expr_neq(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// less or equal
struct expr_leq : public expr_binary
{
	type expr_type;

	expression_desc* l;
	expression_desc* r;

	expr_leq(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// greater or equal
struct expr_geq : public expr_binary
{
	type expr_type;
	expression_desc* l;
	expression_desc* r;

	expr_geq(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// less than
struct expr_lt : public expr_binary
{
	type expr_type;

	expression_desc* l;
	expression_desc* r;

	expr_lt(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// greater than
struct expr_gt : public expr_binary
{
	type expr_type;

	expression_desc* l;
	expression_desc* r;

	expr_gt(int row_number, expression_desc* left, expression_desc* right);

	int get_row();
	var_value get_val();

	void evaluate();
};

// negation (!)
struct expr_neg : public expr_unary
{
	type expr_type;
	expression_desc* e;

	expr_neg(int row_number, expression_desc* ex);

	int get_row();
	var_value get_val();

	void evaluate();
};

// unary minus
struct expr_um : public expr_unary
{
	type expr_type;
	expression_desc* e;

	expr_um(int row_number, expression_desc* ex);

	int get_row();
	var_value get_val();

	void evaluate();
};

/*struct expr_incr : public command_desc
{
	type expr_type;
	expression_desc* e;

	expr_incr(int row_number, expr_var* ex);

	int get_row();
	type get_type();

	void evaluate();
};

struct expr_decr : public command_desc
{
	type expr_type;
	expression_desc* e;

	expr_decr(int row_number, expression_desc* ex);

	int get_row();
	type get_type();

	void evaluate();
};*/

struct for_3_desc : public command_desc
{
	// int row; // > comment for the same reason
	command_desc* start;

	expression_desc* loop_condition;

	command_desc* iterate;

	command_list_desc* commands;



	for_3_desc(
		int row_number,
		command_desc* start_,
		expression_desc* condition_,
		command_desc* iterate_,
		command_list_desc* commands_
	);

	var_value get_return_value();

	void evaluate();
};

struct for_in_desc : public command_desc
{
	// int row; // > comment for the same reason
	std::string* variable;

	c_expression_list* elements;
	command_list_desc* commands;
	int row;


	for_in_desc(
		int row_number,
		std::string* variable_,
		c_expression_list* cel,
		command_list_desc* commands_
	);

	var_value get_return_value();

	void evaluate();
};


/*struct for_in_var_desc : public command_desc
{
	// int row; // > comment for the same reason
	std::string* variable;

	std::string* range;
	command_list_desc* commands;
	int row;


	for_in_var_desc(
		int row_number,
		std::string* variable_,
		std::string* r,
		command_list_desc* commands_
	);

	var_value get_return_value();

	void evaluate();
};*/

struct if_desc : public command_desc
{
	// int row; // > comment for the same reason
	expression_desc* condition;
	command_list_desc* commands_pos;	// positive
	command_list_desc* commands_neg; 	// negative

	if_desc(
		int row_number,
		expression_desc* condition_,
		command_list_desc* commands_pos_,
		command_list_desc* commands_neg_
	);

	var_value get_return_value();

	void evaluate();
};

struct while_desc : public command_desc
{
	// int row; // > comment for the same reason
	expression_desc* loop_condition;
	command_list_desc* commands;

	while_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	var_value get_return_value();

	void evaluate();
};

struct until_desc : public command_desc
{
	// int row; // > comment for the same reason
	expression_desc* loop_condition;
	command_list_desc* commands;

	until_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	var_value get_return_value();

	void evaluate();
};

struct casepart
{
	expression_desc* condition;
	command_list_desc* command;

	casepart(expression_desc* cn, command_list_desc* cm);

	void evaluate();
};

struct casepartvector
{
	std::vector<casepart*> case_parts;

	casepartvector();

	void add(casepart* cp);
	void add(casepartvector* other);
};

struct case_desc : public command_desc
{
	// int row; // > comment for the same reason
	expression_desc* case_expr;
	std::vector<casepart*> case_parts;
	command_list_desc* defaultcase;

	case_desc(int row_number, expression_desc* case_expr_, casepartvector* caseparts_, command_list_desc* dcase);

	var_value get_return_value();

	void evaluate();
};

// a command which is an expression
struct command_expr : public command_desc
{
	expression_desc* e;
	var_value result;

	command_expr(expression_desc* ex);

	var_value get_return_value();

	void evaluate();
};

struct argumentsvector
{
	std::vector<expression_desc*> arguments;
	bool is_empty;

	argumentsvector();

	void add(expression_desc* e);
	void add(argumentsvector* other);
};

// calls a command
struct call : public command_desc
{
	std::string name;
	std::vector<expression_desc*> args;
	// int row; // > comment for the same reason
	var_value returnval;


	call(std::string n, argumentsvector* a, int row_number);

	var_value get_return_value();

	void evaluate();
};

// the stack of symbol tables (for shadowing)
struct sytable_stack : public command_desc
{
	command_list_desc* c;

	sytable_stack(command_list_desc* cd);


	var_value get_return_value();

	void evaluate();
};

#endif
