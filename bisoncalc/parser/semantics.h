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




struct expression_desc
{
	expression_desc(int row_number, type data_type) : row(row_number), expr_type(data_type) {}
	expression_desc(int row_number, type data_type, int value) : row(row_number), expr_type(data_type), intval(value) {}
	//expression_desc(expression_desc* other) : row(other->row), expr_type(other->expr_type) {}
	//expression_desc(command_list_desc* cld) : row(cld->get_row()), intval(cld->get_value){}
	expression_desc(){}

	int row;
	type expr_type;
	/*union{
		int intval;
		double doubleval;
		std::string strval;
	};*/
	int intval;

	

	void set_row(int &r);
	int get_row();
	virtual int get_value() = 0;
	virtual void evaluate() = 0;
	virtual type get_type() = 0;
	
};

struct command_desc
{

	command_desc(int row_number) : row(row_number) {}
	command_desc(){}
	//command_desc(expression_desc* ex) : row(ex->get_row()), intval(ex->get_value()) {}

	int row;
	//int intval;

	void set_row(int &r);
	int get_row();
	virtual void evaluate() = 0;
	//int get_value();
};

struct command_list_desc
{
	command_list_desc(command_list_desc* other);
	command_list_desc();
	//command_list_desc(command_desc* c) : row(c->get_row()), intval(c->get_value()){}

	std::vector<command_desc*> command_list;
	int row;
	//int intval;

	//int get_value();
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
};

struct expr_unary : public expression_desc
{
	expr_unary(int row_number, expression_desc* ex) : row(row_number), e(ex) {}
	expr_unary(){}

	int row;
	expression_desc* e;
	type expr_type;
};

struct expr_const : public expression_desc
{
	expr_const(int row_number, int value, type var_type);

	int row;
	int intval;
	type expr_type;
	
	int get_value();
	void evaluate();
	type get_type();
};

struct expr_var : public expression_desc
{
	expr_var(int row_number, std::string var_name);

	int row;
	std::string name;
	
	type expr_type;
	int intval;

	int get_value();
	void evaluate();
	type get_type();
};

struct expr_asg : public expression_desc
{
	expr_asg(int row_number, std::string* var_name, expression_desc* ex);
	int row;
	std::string* vname;
	expression_desc* e;
	type expr_type;

	int get_value();
	std::string get_name();
	void evaluate();
	type get_type();
};

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

struct expr_par : public expr_unary
{
	expr_par(int row_number, expression_desc* nested);

	
	int row;
	expression_desc* e;
	int intval;
	type expr_type;

	int get_value();
	void evaluate();
	type get_type();
};

struct expr_add : public expr_binary
{
	expr_add(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_dif : public expr_binary
{
	expr_dif(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_mul : public expr_binary
{
	expr_mul(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_div : public expr_binary
{
	expr_div(int row_number, expression_desc* left, expression_desc* right);

	int row;	
	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;


	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_pow : public expr_binary
{
	expr_pow(int row_number, expression_desc* left, expression_desc* right);
	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_mod : public expr_binary
{
	expr_mod(int row_number, expression_desc* left, expression_desc* right);

	int row;
	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_or : public expr_binary
{
	expr_or(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_and : public expr_binary
{
	expr_and(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_eq : public expr_binary
{
	expr_eq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_neq : public expr_binary
{
	expr_neq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_leq : public expr_binary
{
	expr_leq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_geq : public expr_binary
{
	expr_geq(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_lt : public expr_binary
{
	expr_lt(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_gt : public expr_binary
{
	expr_gt(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_neg : public expr_unary
{
	expr_neg(int row_number, expression_desc* ex);

	expression_desc* e;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct expr_um : public expr_unary
{
	expr_um(int row_number, expression_desc* ex);

	expression_desc* e;
	int intval;
	type expr_type;

	void evaluate();
	int get_value();
	int get_row();
	type get_type();
};

struct for_3_desc : public command_desc
{
	for_3_desc(int row_number, expression_desc* start_, expression_desc* condition_, expression_desc* iterate_, command_list_desc* commands_);
	
	int row;
	expression_desc* start;
	expression_desc* loop_condition;
	expression_desc* iterate;
	command_list_desc* commands;

	void evaluate();
};

struct for_in_desc : public command_desc
{
	for_in_desc(int row_number, std::string* variable_, c_expression_list* cel, command_list_desc* commands_);

	int row;
	std::string* variable;
	c_expression_list* elements;
	command_list_desc* commands;
	
	void evaluate();
};

struct if_desc : public command_desc
{
	if_desc(int row_number, expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_);

	int row;
	expression_desc* condition;
	command_list_desc* commands_pos;
	command_list_desc* commands_neg;

	void evaluate();
};

struct while_desc : public command_desc
{
	while_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	int row;
	expression_desc* loop_condition;
	command_list_desc* commands;

	void evaluate();
};

struct until_desc : public command_desc
{
	until_desc(int row_number, expression_desc* condition_, command_list_desc* commands_);

	int row;
	expression_desc* loop_condition;
	command_list_desc* commands;

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
	
	

	void evaluate();
};

struct command_expr : public command_desc
{
	command_expr(expression_desc* ex);
	expression_desc* e;

	void evaluate();
};

//struct sytable_stack : public command_desc
//{
//	sytable_stack(command_list_desc* cd);
//}

#endif
