#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <journal/journal.h>
#include "symbol_table.h"
//#include "../functions.h"



//generic expression class
struct expression_desc
{
	expression_desc(int row_number, var_value v);
	expression_desc(){}
	virtual ~expression_desc();

	int row;
	var_value val;

	void set_row(int &r);
	int get_row();
	virtual var_value get_val() = 0;
	virtual void evaluate() = 0;
	type get_type();
	
};

struct command_desc
{
	command_desc(int row_number) : row(row_number) {}
	command_desc(){}

	int row;

	virtual var_value get_return_value() = 0;
	void set_row(int &r);
	int get_row();
	virtual void evaluate() = 0;
};

struct command_list_desc
{
	command_list_desc(command_list_desc* other);
	command_list_desc();

	std::vector<command_desc*> command_list;
	int row;

	int get_row();
	void add(command_desc* cd);
	void add(command_list_desc* other);
	void evaluate();
};

struct expr_binary : public expression_desc
{
	expr_binary(int row_number, expression_desc* left, expression_desc* right) :  row(row_number), l(left), r(right) {}
	expr_binary(){}

	int row;
	expression_desc* l;
	expression_desc* r;
	type expr_type;
	virtual var_value get_val() = 0;
};

struct expr_unary : public expression_desc
{
	expr_unary(int row_number, expression_desc* ex) : row(row_number), e(ex) {}
	expr_unary(){}

	int row;
	expression_desc* e;
	type expr_type;
	virtual var_value get_val() = 0;
};

//constant values
struct expr_const : public expression_desc
{
	expr_const(int row_number, var_value v);
	expr_const(int row_number);

	int row;
	
	var_value get_val();
	void evaluate();
	type get_type();
};

//variables
struct expr_var : public expression_desc
{
	expr_var(int row_number, std::string var_name);

	int row;
	std::string name;
	
	var_value get_val();
	void evaluate();
	type get_type();
};

struct expr_arr : public expression_desc
{
	expr_arr(int row_number, expr_arr* a);
	expr_arr(int row_number);

	int row;
	int size;
	var_value val;

	var_value get_val();
	void deleteBecauseGccPolymorphicSucks();
	void add(expression_desc* e);
	//void add(std::string s, expression_desc* e);
	void add(expression_desc* variable, expression_desc* varvalue);
	void evaluate();
	type get_type();
	int get_size();
};

//assignment
struct assign : public command_desc
{
	assign(int row_number, std::string* var_name, expression_desc* ex);
	int row;
	std::string* vname;
	expression_desc* e;
	
	var_value get_return_value();
	std::string get_name();
	void evaluate();
};

//assignment for local variables (shadowing)
struct local_assign : public command_desc
{
	local_assign(int row_number, std::string* var_name, expression_desc* ex);
	int row;
	std::string* vname;
	expression_desc* e;
	
	var_value get_return_value();
	std::string get_name();
	void evaluate();
};

//expression list to store an array of expressions (for_in)
struct c_expression_list
{
	c_expression_list(){}
	c_expression_list(c_expression_list* other);
	std::vector<expression_desc*> expr_list;
	void add(expression_desc* e);
	void add(c_expression_list* other);
	int get_size();
	expression_desc* return_element(unsigned int i);
};

//paranthesis ()
struct expr_par : public expr_unary
{
	expr_par(int row_number, expression_desc* nested);

	int row;
	expression_desc* e;
	
	var_value get_val();
	void evaluate();
	type get_type();
};

//array element []
struct expr_ael : public expression_desc
{
	expr_ael(int row_number, std::string var_name, expression_desc* n);

	int row;
	std::string name;
	expression_desc* nth;
	
	var_value get_val();
	void evaluate();
	type get_type();
};

//operator +
struct expr_add : public expr_binary
{
	expr_add(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator -
struct expr_dif : public expr_binary
{
	expr_dif(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;

	var_value get_val();	
	void evaluate();
	int get_row();
	type get_type();
};

//operator *
struct expr_mul : public expr_binary
{
	expr_mul(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator /
struct expr_div : public expr_binary
{
	expr_div(int row_number, expression_desc* left, expression_desc* right);

	int row; //???? ez kell ide?	
	expression_desc* l;
	expression_desc* r;

	var_value get_val();	
	void evaluate();
	int get_row();
	type get_type();
};

//operator ^ (alternative **)
struct expr_pow : public expr_binary
{
	expr_pow(int row_number, expression_desc* left, expression_desc* right);
	expression_desc* l;
	expression_desc* r;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator %
struct expr_mod : public expr_binary
{
	expr_mod(int row_number, expression_desc* left, expression_desc* right);

	int row;
	expression_desc* l;
	expression_desc* r;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator -o
struct expr_or : public expr_binary
{
	expr_or(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator -a
struct expr_and : public expr_binary
{
	expr_and(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;
	
	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator -eq (equals)
struct expr_eq : public expr_binary
{
	expr_eq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;

	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//operator -neq (not equal)
struct expr_neq : public expr_binary
{
	expr_neq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;

	var_value get_val();
	void evaluate();	
	int get_row();
	type get_type();
};

//less or equal
struct expr_leq : public expr_binary
{
	expr_leq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;
	
	var_value get_val();
	void evaluate();	
	int get_row();
	type get_type();
};

//greater or equal
struct expr_geq : public expr_binary
{
	expr_geq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;

	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

//less than
struct expr_lt : public expr_binary
{
	expr_lt(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;

	var_value get_val();
	void evaluate();	
	int get_row();
	type get_type();
};

//greater than
struct expr_gt : public expr_binary
{
	expr_gt(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	type expr_type;

	var_value get_val();
	void evaluate();	
	int get_row();
	type get_type();
};

//negation (!)
struct expr_neg : public expr_unary
{
	expr_neg(int row_number, expression_desc* ex);

	expression_desc* e;
	type expr_type;

	var_value get_val();
	void evaluate();	
	int get_row();
	type get_type();
};

//unary minus
struct expr_um : public expr_unary
{
	expr_um(int row_number, expression_desc* ex);

	expression_desc* e;
	type expr_type;

	var_value get_val();
	void evaluate();
	int get_row();
	type get_type();
};

/*struct expr_incr : public command_desc
{
	expr_incr(int row_number, expr_var* ex);
	
	expression_desc* e;
	type expr_type;

	void evaluate();
	int get_row();
	type get_type();
};

struct expr_decr : public command_desc
{
	expr_decr(int row_number, expression_desc* ex);
	
	expression_desc* e;
	type expr_type;

	void evaluate();
	int get_row();
	type get_type();
};*/

struct for_3_desc : public command_desc
{
	for_3_desc(int row_number, command_desc* start_, expression_desc* condition_, command_desc* iterate_, command_list_desc* commands_);

	int row;
	command_desc* start;
	expression_desc* loop_condition;
	command_desc* iterate;
	command_list_desc* commands;

	var_value get_return_value();
	void evaluate();
};

struct for_in_desc : public command_desc
{
	for_in_desc(int row_number, std::string* variable_, c_expression_list* cel, command_list_desc* commands_);

	int row;
	std::string* variable;
	c_expression_list* elements;
	command_list_desc* commands;
	
	var_value get_return_value();
	void evaluate();
};

struct if_desc : public command_desc
{
	if_desc(int row_number, expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_);

	int row;
	expression_desc* condition;
	command_list_desc* commands_pos;	//positive
	command_list_desc* commands_neg; 	//negative

	var_value get_return_value();
	void evaluate();
};

struct while_desc : public command_desc
{
	while_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	int row;
	expression_desc* loop_condition;
	command_list_desc* commands;

	var_value get_return_value();
	void evaluate();
};

struct until_desc : public command_desc
{
	until_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	int row;
	expression_desc* loop_condition;
	command_list_desc* commands;

	var_value get_return_value();
	void evaluate();
};

struct casepart
{
	casepart(expression_desc* cn, command_list_desc* cm);
	expression_desc* condition;
	command_list_desc* command;
	
	void evaluate();
};

struct casepartvector
{
	casepartvector();
	std::vector<casepart*> case_parts;

	void add(casepart* cp);
	void add(casepartvector* other);
};

struct case_desc : public command_desc
{
	case_desc(int row_number, expression_desc* case_expr_, casepartvector* caseparts_, command_list_desc* dcase);

	int row;
	expression_desc* case_expr;
	std::vector<casepart*> case_parts;
	command_list_desc* defaultcase;
	
	var_value get_return_value();
	void evaluate();
};

//a command which is an expression
struct command_expr : public command_desc
{
	command_expr(expression_desc* ex);
	expression_desc* e;
	var_value result;

	var_value get_return_value();
	void evaluate();
};

struct argumentsvector
{
	argumentsvector();
	std::vector<expression_desc*> arguments;
	bool is_empty;

	void add(expression_desc* e);
	void add(argumentsvector* other);
};

//calls a command
struct call : public command_desc
{
	call(std::string n, argumentsvector* a, int row_number);


	std::string name;
	std::vector<expression_desc*> args;
	int row;
	var_value returnval;

	var_value get_return_value();
	void evaluate();
};

//the stack of symbol tables (for shadowing)
struct sytable_stack : public command_desc
{
	sytable_stack(command_list_desc* cd);
	
	command_list_desc* c;

	var_value get_return_value();
	void evaluate();
};

#endif
