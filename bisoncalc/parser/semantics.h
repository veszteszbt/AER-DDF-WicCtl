#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <journal/journal.h>


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
	command_list_desc(){}
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
	for_3_desc(expression_desc* start_, expression_desc* condition_, expression_desc* iterate_, command_list_desc* commands_);
	expression_desc* start;
	expression_desc* loop_condition;
	expression_desc* iterate;
	command_list_desc* commands;

	void evaluate();
};

struct for_in_desc : public command_desc
{
	for_in_desc(expression_desc* variable_, expression_desc* loop_expr_, command_list_desc* commands_) :
	variable(variable_), loop_expr(loop_expr_), commands(commands_) {}

	expression_desc* variable;
	expression_desc* loop_expr;
	command_list_desc* commands;
	
	void evaluate();
};

struct if_desc : public command_desc
{
	if_desc(expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_) : 
	condition(condition_), commands_pos(commands_pos_), commands_neg(commands_neg_) {}

	expression_desc* condition;
	command_list_desc* commands_pos;
	command_list_desc* commands_neg;

	void evaluate();
};

struct while_desc : public command_desc
{
	while_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}

	expression_desc* loop_condition;
	command_list_desc* commands;

	void evaluate();
};

struct until_desc : public command_desc
{
	until_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}

	expression_desc* loop_condition;
	command_list_desc* commands;

	void evaluate();
};

struct case_desc : public command_desc
{
	case_desc(expression_desc* case_expr_, command_list_desc* case_parts_) :
	case_expr(case_expr_), case_parts(case_parts_) {}

	expression_desc* case_expr;
	command_list_desc* case_parts;

	void evaluate();
};

struct command_expr : public command_desc
{
	command_expr(expression_desc* ex);
	expression_desc* e;

	void evaluate();
};

#endif
