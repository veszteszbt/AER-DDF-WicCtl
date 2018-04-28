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

expr_asg::expr_asg(int row_number, std::string* var_name, expression_desc* ex)
{
	intval = ex->intval;
	if (parser.symbol_table.count(*var_name) != 0)
	{
		std::cout << "variable already in, updating value" << std::endl;
		parser.symbol_table[*var_name] = 
		variable_desc(parser.symbol_table[*var_name].decl_row, ex->expr_type, ex->intval);
	}
	else
	{
		std::cout << "new variable" << std::endl;
		parser.symbol_table[*var_name] = variable_desc(row_number, ex->expr_type, ex->intval);
	}
	std::cout << "Assign " << intval << " to variable name " << *var_name << std::endl;
}

int expr_asg::get_value()
{
	return 1;
}

expr_add::expr_add(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	if (left->expr_type == right->expr_type)
	{
		expr_type = left->expr_type;
		evaluate();
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

void expr_add::evaluate()
{
	intval = l->get_value() + r->get_value();
	std::cout << "eredmeny :" << intval << std::endl;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_row()
{
	return row;
}

expr_dif::expr_dif(int row_number, expression_desc* left, expression_desc* right)
{
	if (left->expr_type == right->expr_type)
	{
		expr_type = left->expr_type;
		evaluate();
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

void expr_dif::evaluate()
{
	intval = l->get_value() - r->get_value();
	std::cout << "eredmeny :" << intval << std::endl;
}

int expr_par::get_value()
{
	return intval;
}

expr_mul::expr_mul(int row_number, expression_desc* left, expression_desc* right){
	if (left->expr_type == right->expr_type)
	{
		expr_type = left->expr_type;
		evaluate();
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

void expr_mul::evaluate()
{
	std::cout << "left: " << l->intval << "*" << "right: " << r->intval << std::endl;
	intval = l->intval * r->intval;
	std::cout << "eredmeny :" << intval << std::endl;
}

int expr_mul::get_value()
{
	return intval;
}

/*int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}

int expr_add::get_value()
{
	return intval;
}
*/
