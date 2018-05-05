#include "semantics.h"
#include "Parser.ih"

extern Parser parser;


void expression_desc::set_row(int &r)
{
	row = r;
}

int expression_desc::get_row()
{
	return row;
}

int expression_desc::get_value()
{
	//std::cout << "expression_desc" << intval << std::endl;
	return intval;
}

void command_desc::set_row(int &r)
{
	row = r;
}

int command_desc::get_row()
{
	return row;
}

/*int command_desc::get_value()
{
    return intval;
}*/

command_list_desc::command_list_desc(command_list_desc* other)
{
	unsigned int osize = other->command_list.size();
	command_list.resize(osize);
	for(unsigned int i=0;i<osize;i++)
	{
		command_list[i] = other->command_list[i];
	}
}

/*int command_list_desc::get_value()
{
	return intval;
}*/

int command_list_desc::get_row()
{
	return row;
}

void command_list_desc::add(command_desc* cd)
{
	command_list.push_back(*cd);
}

void command_list_desc::add(command_list_desc* other)
{
	for(unsigned int i=0;i<other->command_list.size();i++)
	{
		command_list.push_back(other->command_list[i]);
	}
	delete other;
}

int expr_const::get_value()
{
	return intval;
}

void expr_const::evaluate()
{
	//std::cout << "evaluate expr_const: " << intval << std::endl;
}

type expr_const::get_type()
{
	return expr_type;
}

expr_var::expr_var(int row_number, std::string var_name) : row(row_number), name(var_name)
{
	auto it = parser.symbol_table.find(name);
	if (it == parser.symbol_table.end())
	{
		std::cerr << row << ": ERROR: Variable " << name << " has no value yet!" << std::endl;
		exit(1);
	}
	else
	{
		variable_desc v = it->second;
		intval = v.intval;
		//std::cout << "get value " << intval << " (was " << v.intval << ") from symbol table for vname " << name << std::endl;
		row = v.decl_row;
		expr_type = v.var_type;
	}
}

int expr_var::get_value()
{
	//std::cout << "expr_var::get_value() :" << intval << std::endl;
	return intval;
}

void expr_var::evaluate()
{
	//std::cout << "evaluate expr_var: " << intval << std::endl;
}

type expr_var::get_type()
{
	return expr_type;
}

expr_asg::expr_asg(int row_number, std::string* var_name, expression_desc* ex)
{
	intval = ex->get_value();
	expr_type = ex->get_type();
	//std::cout << "ex->get_value() " << ex->get_value() << ", intval " << intval << std::endl;
	if (parser.symbol_table.count(*var_name) != 0)
	{
		//std::cout << "variable already in, updating value" << std::endl;
		parser.symbol_table[*var_name] = 
		variable_desc(parser.symbol_table[*var_name].decl_row, expr_type, intval);
	}
	else
	{
		//std::cout << "new variable" << std::endl;
		parser.symbol_table[*var_name] = variable_desc(row_number, expr_type, intval);
	}
	//std::cout << "Assign " << intval << " to variable name " << *var_name << std::endl;
}

int expr_asg::get_value()
{
	return 1;
}

void expr_asg::evaluate()
{}

type expr_asg::get_type()
{
	return expr_type;
}

expr_par::expr_par(int row_number, expression_desc* nested) : row(row_number), e(nested)
{
	evaluate();
	//std::cout << "row:" << row << std::endl;
	//std::cout << "nested->get_row():" << e->get_row() << std::endl;
	//std::cout << "intval:" << intval << std::endl;
	//std::cout << "nested->get_value():" << e->get_value() << std::endl;
}

int expr_par::get_value()
{
	return intval;
}

void expr_par::evaluate()
{
	intval = e->get_value();
	expr_type = e->get_type();
	//std::cout << "evaluate expr_par: " << intval << std::endl;
}

type expr_par::get_type()
{
	return expr_type;
}

expr_add::expr_add(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	if (left->get_type() == right->get_type())
	{
		expr_type = left->get_type();
		evaluate();
	}
	else
	{
		if (left->get_type()==u_string || right->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
}

void expr_add::evaluate()
{
	intval = l->get_value() + r->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_add::get_value()
{
	evaluate();
	//std::cout << "evaluate" << std::endl;
	return intval;
}

int expr_add::get_row()
{
	return row;
}

type expr_add::get_type()
{
	return expr_type;
}

expr_dif::expr_dif(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	if (left->get_type() == right->get_type())
	{
		expr_type = left->get_type();
		evaluate();
	}
	else
	{
		if (left->get_type()==u_string || right->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
}

void expr_dif::evaluate()
{
	intval = l->get_value() - r->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_dif::get_row()
{
	return row;
}

int expr_dif::get_value()
{
	return intval;
}

type expr_dif::get_type()
{
	return expr_type;
}

expr_mul::expr_mul(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	if (left->get_type() == right->get_type())
	{
		expr_type = left->get_type();
		evaluate();
	}
	else
	{
		if (left->get_type()==u_string || right->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
}

void expr_mul::evaluate()
{
	//std::cout << "left: " << l->get_value() << "*" << "right: " << r->get_value() << std::endl;
	intval = l->get_value() * r->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_mul::get_value()
{
	return intval;
}

type expr_mul::get_type()
{
	return expr_type;
}

expr_div::expr_div(int row_number, expression_desc* left, expression_desc* right)  : row(row_number), l(left), r(right)
{
	if (left->get_type() == right->get_type())
	{
		if (right->get_value() == 0)
		{
			std::cerr << row << ": ERROR: division by 0" << std::endl;
			exit(1);
		}
		else
		{
			expr_type = left->get_type();
			evaluate();
		}
	}
	else
	{
		if (left->get_type()==u_string || right->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
}

void expr_div::evaluate()
{
	intval = l->get_value() / r->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_div::get_row()
{
	return row;
}

int expr_div::get_value()
{
	return intval;
}

type expr_div::get_type()
{
	return expr_type;
}

expr_pow::expr_pow(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	if (left->get_type() == right->get_type())
	{
		expr_type = left->get_type();
		intval = pow(left->get_value(), right->get_value());
		//std::cout << "eredmeny :" << intval << std::endl;
	}
	else
	{
		if (left->get_type()==u_string || right->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
}

void expr_pow::evaluate()
{
	intval = pow(l->get_value(), r->get_value());
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_pow::get_row()
{
	return row;
}

int expr_pow::get_value()
{
	return intval;
}

type expr_pow::get_type()
{
	return expr_type;
}

expr_mod::expr_mod(int row_number, expression_desc* left, expression_desc* right) : row(row_number), l(left), r(right)
{
	if(left->get_type()==u_integer && right->get_type()==u_integer){
		if (right->get_value()!=0)
		{
			expr_type = u_integer;
			evaluate();
		}
		else
		{
			std::cerr << row << ": ERROR: modulo cannot be 0!" << std::endl;
			exit(1);
		}
	}
	else{
		std::cerr << row << ": ERROR: modulo operator only accepts integer type!" << std::endl;
	}
}

void expr_mod::evaluate()
{
	intval = l->get_value() % r->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_mod::get_row()
{
	return row;
}

int expr_mod::get_value()
{
	return intval;
}

type expr_mod::get_type()
{
	return expr_type;
}

expr_or::expr_or(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_or::evaluate()
{
	if (l->get_value() != 0 || r->get_value() != 0)
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_or::get_row()
{
	return row;
}

int expr_or::get_value()
{
	return intval;
}

type expr_or::get_type()
{
	return expr_type;
}

expr_and::expr_and(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_and::evaluate()
{
	if (l->get_value() != 0 && r->get_value() != 0)
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_and::get_row()
{
	return row;
}

int expr_and::get_value()
{
	return intval;
}

type expr_and::get_type()
{
	return expr_type;
}

expr_eq::expr_eq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_eq::evaluate()
{
	if (l->get_value() == r->get_value())
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_eq::get_row()
{
	return row;
}

int expr_eq::get_value()
{
	return intval;
}

type expr_eq::get_type()
{
	return expr_type;
}

expr_neq::expr_neq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_neq::evaluate()
{
	if (l->get_value() != r->get_value())
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_neq::get_row()
{
	return row;
}

int expr_neq::get_value()
{
	return intval;
}

type expr_neq::get_type()
{
	return expr_type;
}

expr_leq::expr_leq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_leq::evaluate()
{
	if (l->get_value() > r->get_value())
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_leq::get_row()
{
	return row;
}

int expr_leq::get_value()
{
	return intval;
}

type expr_leq::get_type()
{
	return expr_type;
}

expr_geq::expr_geq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_geq::evaluate()
{
	if (l->get_value() < r->get_value())
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_geq::get_row()
{
	return row;
}

int expr_geq::get_value()
{
	return intval;
}

type expr_geq::get_type()
{
	return expr_type;
}

expr_lt::expr_lt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_lt::evaluate()
{
	if (l->get_value() < r->get_value())
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_lt::get_row()
{
	return row;
}

int expr_lt::get_value()
{
	return intval;
}

type expr_lt::get_type()
{
	return expr_type;
}

expr_gt::expr_gt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	evaluate();
	expr_type = u_integer;
}

void expr_gt::evaluate()
{
	if (l->get_value() > r->get_value())
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_gt::get_row()
{
	return row;
}

int expr_gt::get_value()
{
	return intval;
}

type expr_gt::get_type()
{
	return expr_type;
}

expr_neg::expr_neg(int row_number, expression_desc* ex) : e(ex)
{
	expr_type = u_integer;
	evaluate();
}

void expr_neg::evaluate()
{
	if (e->get_value() != 0)
	{
		intval = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		intval = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_neg::get_row()
{
	return row;
}

int expr_neg::get_value()
{
	return intval;
}

type expr_neg::get_type()
{
	return expr_type;
}

expr_um::expr_um(int row_number, expression_desc* ex) : e(ex)
{
	expr_type = u_integer;
	evaluate();
}

void expr_um::evaluate()
{
	expr_type = e->get_type();
	intval = -1 * e->get_value();
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_um::get_row()
{
	return row;
}

int expr_um::get_value()
{
	return intval;
}

type expr_um::get_type()
{
	return expr_type;
}

