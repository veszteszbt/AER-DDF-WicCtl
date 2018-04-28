#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>


enum type{ u_integer, u_double, u_string };

struct variable_desc
{
	variable_desc(int row_number, type data_type, int value=0) : decl_row(row_number), var_type(data_type), intval(value) {}
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

	//virtual void evaluate()  = 0;

	void set_row(int &r);
	int get_row();
	//virtual int get_value() =0;
	int get_value();
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
	//int get_value();
};

struct command_list_desc
{
	command_list_desc(command_list_desc* other);
	command_list_desc(){}
	//command_list_desc(command_desc* c) : row(c->get_row()), intval(c->get_value()){}

	std::vector<command_desc> command_list;
	int row;
	//int intval;

	//int get_value();
	int get_row();
	void add(command_desc* cd);
	void add(command_list_desc* other);
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


//extern std::map<std::string, variable_desc> Parser::symbol_table;

struct expr_asg : public expr_unary
{
	expr_asg(int row_number, std::string* var_name, expression_desc* ex);
	std::string* var_name;
	expression_desc* value;
	int get_value();
};

struct expr_par : public expr_unary
{
	expr_par(int row_number, expression_desc* nested) : row(row_number), intval(nested->get_value()){
		std::cout << "row:" << row << std::endl;
		std::cout << "nested->get_row():" << nested->get_row() << std::endl;
		std::cout << "intval:" << intval << std::endl;
		std::cout << "nested->get_value():" << nested->get_value() << std::endl;
	}

	int row;
	int intval;

	int get_value();
};

struct expr_add : public expr_binary
{
	expr_add(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;

	void evaluate();
	int get_value();
	int get_row();
};

struct expr_dif : public expr_binary
{
	expr_dif(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;

	void evaluate();
	int get_value();
	int get_row();
};

struct expr_mul : public expr_binary
{
	expr_mul(int row_number, expression_desc* left, expression_desc* right);

	expression_desc* l;
	expression_desc* r;
	int intval;

	void evaluate();
	int get_value();
	int get_row();
};

struct expr_div : public expr_binary
{
	expr_div(int row_number, expression_desc* left, expression_desc* right){
		if (left->expr_type == right->expr_type)
		{
			if (right->intval == 0)
			{
				std::cout << "ERROR: division by 0" << std::endl;
				exit(1);
			}
			else
			{
				expr_type = left->expr_type;
				intval = left->intval / right->intval;
				std::cout << "eredmeny :" << intval << std::endl;
			}
		}
		else
		{
			if (left->expr_type==u_string || right->expr_type==u_string)
			{
				expr_type = u_string;
			}
			else
			{
				expr_type = u_double;
			}
		}
	}
};

struct expr_pow : public expr_binary
{
	expr_pow(int row_number, expression_desc* left, expression_desc* right){
		if (left->expr_type == right->expr_type)
		{
			expr_type = left->expr_type;
			intval = pow(left->intval, right->intval);
			std::cout << "eredmeny :" << intval << std::endl;
		}
		else
		{
			if (left->expr_type==u_string || right->expr_type==u_string)
			{
				expr_type = u_string;
			}
			else
			{
				expr_type = u_double;
			}
		}
	}
};

struct expr_mod : public expr_binary
{
	expr_mod(int row_number, expression_desc* left, expression_desc* right){
		if(left->expr_type==u_integer && right->expr_type==u_integer){
			expr_type = u_integer;
			intval = left->intval % right->intval;
			std::cout << "eredmeny :" << intval << std::endl;
		}
		else{
			//error
		}
	}
};

struct expr_or : public expr_binary
{
	expr_or(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval != 0 || right->intval != 0)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_and : public expr_binary
{
	expr_and(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval != 0 && right->intval != 0)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_eq : public expr_binary
{
	expr_eq(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval == right->intval)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_neq : public expr_binary
{
	expr_neq(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval != right->intval)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_leq : public expr_binary
{
	expr_leq(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval > right->intval)
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		else
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_geq : public expr_binary
{
	expr_geq(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval < right->intval)
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		else
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_lt : public expr_binary
{
	expr_lt(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval < right->intval)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_gt : public expr_binary
{
	expr_gt(int row_number, expression_desc* left, expression_desc* right){
		if (left->intval > right->intval)
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		expr_type = u_integer;
	}
};

struct expr_neg : public expr_unary
{
	expr_neg(int row_number, expression_desc* ex){
		expr_type = u_integer;
		if (ex->intval != 0)
		{
			intval = 0;
			std::cout << "FALSE" << std::endl;
		}
		else
		{
			intval = 1;
			std::cout << "TRUE" << std::endl;
		}
	}
};

struct expr_um : public expr_unary
{
	expr_um(int row_number, expression_desc* ex){
		expr_type = ex->expr_type;
		intval = -1 * ex->intval;
		std::cout << "eredmeny :" << intval << std::endl;
	}
};

struct for_3_desc : public command_desc
{
	for_3_desc(expr_asg* start_, expression_desc* condition_, expression_desc* iterate_, command_list_desc* commands_) :
	 start(start_), loop_condition(condition_), iterate(iterate_), commands(commands_) {}

	expr_asg* start;
	expression_desc* loop_condition;
	expression_desc* iterate;
	command_list_desc* commands;
};

struct for_in_desc : public command_desc
{
	for_in_desc(expression_desc* variable_, expression_desc* loop_expr_, command_list_desc* commands_) :
	variable(variable_), loop_expr(loop_expr_), commands(commands_) {}

	expression_desc* variable;
	expression_desc* loop_expr;
	command_list_desc* commands;
};

struct if_desc : public command_desc
{
	if_desc(expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_) : 
	condition(condition_), commands_pos(commands_pos_), commands_neg(commands_neg_) {}

	expression_desc* condition;
	command_list_desc* commands_pos;
	command_list_desc* commands_neg;
};

struct while_desc : public command_desc
{
	while_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}

	expression_desc* loop_condition;
	command_list_desc* commands;
};

struct until_desc : public command_desc
{
	until_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}

	expression_desc* loop_condition;
	command_list_desc* commands;
};

struct case_desc : public command_desc
{
	case_desc(expression_desc* case_expr_, command_list_desc* case_parts_) :
	case_expr(case_expr_), case_parts(case_parts_) {}

	expression_desc* case_expr;
	command_list_desc* case_parts;
};

#endif
