#include "semantics.h"
#include "Parser.ih"

extern Parser* parser;

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

/*void command_desc::evaluate()
{

}*/

/*int command_desc::get_value()
{
    return intval;
}*/

command_list_desc::command_list_desc()
{
}

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
	return command_list.size();
}*/

int command_list_desc::get_row()
{
	return row;
}

void command_list_desc::add(command_desc* cd)
{
	command_list.push_back(cd);
}

void command_list_desc::add(command_list_desc* other)
{
	for(unsigned int i=0;i<other->command_list.size();i++)
	{
		command_list.push_back(other->command_list[i]);
	}
	//delete other;
}

void command_list_desc::evaluate()
{
	for (std::vector<command_desc*>::iterator it = command_list.begin(); it != command_list.end();++it)
	{
		(*it)->evaluate();
	}
}


expr_const::expr_const(int row_number, int value, type var_type) : row(row_number), intval(value), expr_type(var_type)
{
	//std::cout << intval << std::endl;
}

int expr_const::get_value()
{
	evaluate();
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
	//evaluate();
}

int expr_var::get_value()
{
	//std::cout << "expr_var::get_value() :" << intval << std::endl;
	evaluate();
	return intval;
}

void expr_var::evaluate()
{
	auto it = (*parser).symbol_table.find(name);
	if (it == (*parser).symbol_table.end())
	{
		std::cerr << row << ": ERROR: Variable " << name << " has no value yet!" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: Variable " << name << " has no value yet!" << journal::end;
		std::terminate();
	}
	else
	{
		variable_desc v = it->second;
		intval = v.intval;
		//std::cout << name << " = " << intval << std::endl;
		row = v.decl_row;
		expr_type = v.var_type;
	}
}

type expr_var::get_type()
{
	return expr_type;
}

expr_asg::expr_asg(int row_number, std::string* var_name, expression_desc* ex) : row(row_number), vname(var_name), e(ex)
{
	//std::cout << "asg constructor" << std::endl;
	//std::cout << "asg constructed" << std::endl;
	//std::cout << "ex->get_value() " << ex->get_value() << ", intval " << intval << std::endl;
	//evaluate();
}

int expr_asg::get_value()
{
	//std::cout << "asg::get_value()" << std::endl;
	//evaluate();
	return e->get_value();
}

std::string expr_asg::get_name(){
	return *vname;
}

void expr_asg::evaluate()
{
	//std::cout << "asg::evaluate()" << std::endl;
	//std::cout << "starting asg evaluate" << std::endl;
	e->evaluate();
	intval = e->get_value();
	expr_type = e->get_type();

	if ((*parser).symbol_table.count(*vname) != 0)
	{
		//std::cout << "variable already in, updating value" << std::endl;
		(*parser).symbol_table[*vname] = 
		variable_desc((*parser).symbol_table[*vname].decl_row, expr_type, intval);
	}
	else
	{
		//std::cout << "new variable" << std::endl;
		(*parser).symbol_table[*vname] = variable_desc(row, expr_type, intval);
	}
	//std::cout << "assigned " << intval << " to variable " << (*vname) << std::endl; 
	//std::cout << "asg evaluated" << std::endl;
	journal(journal::info, "semantics") << "Assigned " << intval << " to variable name " << (*vname) << journal::end;
}

type expr_asg::get_type()
{
	return expr_type;
}

expr_par::expr_par(int row_number, expression_desc* nested) : row(row_number), e(nested)
{
	//evaluate();
	//std::cout << "row:" << row << std::endl;
	//std::cout << "nested->get_row():" << e->get_row() << std::endl;
	//std::cout << intval << std::endl;
	//std::cout << "nested->get_value():" << e->get_value() << std::endl;
}

int expr_par::get_value()
{
	evaluate();
	return intval;
}

void expr_par::evaluate()
{
	e->evaluate();
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
	//std::cout << "add constructor" << std::endl;
	//std::cout << "add constructed" << std::endl;
	//evaluate();
}

void expr_add::evaluate()
{
	//std::cout << "add::evaluate()" << std::endl;
	l->evaluate();
	r->evaluate();
	if (l->get_type() == r->get_type())
	{
		expr_type = l->get_type();
		intval = l->get_value() + r->get_value();
		//std::cout << intval << std::endl;
	}
	else
	{
		if (l->get_type()==u_string || r->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
	//std::cout << "add evaluated" << std::endl;
}

int expr_add::get_value()
{
	//std::cout << "add::get_value()" << std::endl;
	//std::cout << "returning add value" << std::endl;
	//evaluate();
	//std::cout << "evaluate" << std::endl;
	//std::cout << "intval = " << intval << std::endl;
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
	//evaluate();
}

void expr_dif::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->get_type() == r->get_type())
	{
		expr_type = l->get_type();
		intval = l->get_value() - r->get_value();
		//std::cout << intval << std::endl;
	}
	else
	{
		if (l->get_type()==u_string || r->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_dif::get_row()
{
	return row;
}

int expr_dif::get_value()
{
	//evaluate();
	return intval;
}

type expr_dif::get_type()
{
	return expr_type;
}

expr_mul::expr_mul(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
}

void expr_mul::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->get_type() == r->get_type())
	{
		expr_type = l->get_type();
		intval = l->get_value() * r->get_value();
		//std::cout << intval << std::endl;
	}
	else
	{
		if (l->get_type()==u_string || r->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
	
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_mul::get_value()
{
	//evaluate();
	return intval;
}

type expr_mul::get_type()
{
	return expr_type;
}

expr_div::expr_div(int row_number, expression_desc* left, expression_desc* right)  : row(row_number), l(left), r(right)
{
	//evaluate();
}

void expr_div::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->get_type() == r->get_type())
	{
		if (r->get_value() == 0)
		{
			std::cerr << row << ": ERROR: division by 0" << std::endl;
			journal(journal::info, "semantics") << row << ": ERROR: division by 0" << journal::end;
			std::terminate();
		}
		else
		{
			expr_type = l->get_type();
			intval = l->get_value() / r->get_value();
			//std::cout << intval << std::endl;
		}
	}
	else
	{
		if (l->get_type()==u_string || r->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_div::get_row()
{
	return row;
}

int expr_div::get_value()
{
	//evaluate();
	return intval;
}

type expr_div::get_type()
{
	return expr_type;
}

expr_pow::expr_pow(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
}

void expr_pow::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->get_type() == r->get_type())
	{
		expr_type = l->get_type();
		intval = pow(l->get_value(), r->get_value());
		//std::cout << intval << std::endl;
		//std::cout << "eredmeny :" << intval << std::endl;
	}
	else
	{
		if (l->get_type()==u_string || r->get_type()==u_string)
		{
			expr_type = u_string;
		}
		else
		{
			expr_type = u_double;
		}
	}
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_pow::get_row()
{
	return row;
}

int expr_pow::get_value()
{
	//evaluate();
	return intval;
}

type expr_pow::get_type()
{
	return expr_type;
}

expr_mod::expr_mod(int row_number, expression_desc* left, expression_desc* right) : row(row_number), l(left), r(right)
{
	//evaluate();
}

void expr_mod::evaluate()
{
	l->evaluate();
	r->evaluate();
	if(l->get_type()==u_integer && r->get_type()==u_integer){
		if (r->get_value()!=0)
		{
			expr_type = u_integer;
			intval = l->get_value() % r->get_value();
			//std::cout << intval << std::endl;
		}
		else
		{
			std::cerr << row << ": ERROR: modulo cannot be 0!" << std::endl;
			journal(journal::info, "semantics") << row << ": ERROR: modulo cannot be 0!" << journal::end;
			std::terminate();
		}
	}
	else
	{
		std::cerr << row << ": ERROR: modulo operator only accepts integer type!" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: modulo operator only accepts integer type!" << journal::end;
		std::terminate();
	}
	//std::cout << "eredmeny :" << intval << std::endl;
}

int expr_mod::get_row()
{
	return row;
}

int expr_mod::get_value()
{
	//evaluate();
	return intval;
}

type expr_mod::get_type()
{
	return expr_type;
}

expr_or::expr_or(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_or::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_or::get_type()
{
	return expr_type;
}

expr_and::expr_and(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_and::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_and::get_type()
{
	return expr_type;
}

expr_eq::expr_eq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_eq::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_eq::get_type()
{
	return expr_type;
}

expr_neq::expr_neq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_neq::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_neq::get_type()
{
	return expr_type;
}

expr_leq::expr_leq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_leq::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_leq::get_type()
{
	return expr_type;
}

expr_geq::expr_geq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_geq::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_geq::get_type()
{
	return expr_type;
}

expr_lt::expr_lt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	//std::cout << "lt constructed" << std::endl;
	expr_type = u_integer;
}

void expr_lt::evaluate()
{
	//std::cout << "starting lt evaluate" << std::endl;
	l->evaluate();
	r->evaluate();
	//std::cout << "left " << l->get_value() << " , right " << r->get_value() << std::endl;
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
	//std::cout << "lt evaluated" << std::endl;
}

int expr_lt::get_row()
{
	return row;
}

int expr_lt::get_value()
{
	//std::cout << "returning lt value" << std::endl;
	//evaluate();
	return intval;
}

type expr_lt::get_type()
{
	return expr_type;
}

expr_gt::expr_gt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_gt::evaluate()
{
	l->evaluate();
	r->evaluate();
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
	//evaluate();
	return intval;
}

type expr_gt::get_type()
{
	return expr_type;
}

expr_neg::expr_neg(int row_number, expression_desc* ex) : e(ex)
{
	//evaluate();
	expr_type = u_integer;
}

void expr_neg::evaluate()
{
	e->evaluate();
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
	evaluate();
	return intval;
}

type expr_neg::get_type()
{
	return expr_type;
}

expr_um::expr_um(int row_number, expression_desc* ex) : e(ex)
{
	expr_type = u_integer;
	//evaluate();
	//std::cout << intval << std::endl;
}

void expr_um::evaluate()
{
	e->evaluate();
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
	//evaluate();
	return intval;
}

type expr_um::get_type()
{
	return expr_type;
}

for_3_desc::for_3_desc(int row_number, expression_desc* start_, expression_desc* condition_, expression_desc* iterate_, command_list_desc* commands_): 
row(row_number), start(start_), loop_condition(condition_), iterate(iterate_), commands(commands_) 
{
	//std::cout << "for3 desc" << std::endl;
	//evaluate();
}


void for_3_desc::evaluate()
{
	start->evaluate();
	while(true)
	{
		loop_condition->evaluate();
		//std::cout << "loop value " << loop_condition->get_value() << std::endl;
		if (loop_condition->get_value() == 0)
		{
			break;
		}
		else
		{
			iterate->evaluate(); 
			commands->evaluate();
		}
	}
}

for_in_desc::for_in_desc(int row_number, std::string* variable_, c_expression_list* cel, command_list_desc* commands_) : variable(variable_), elements(cel), commands(commands_)
{
	//evaluate();
}

void for_in_desc::evaluate()
{
	for(int i=0;i<elements->return_size();i++)
	{
		expr_asg* a = new expr_asg(row, variable, elements->return_element(i));
		a->evaluate();
		//std::cout << a->get_value() << "a value" << std::endl;
		commands->evaluate();
	}
}

command_expr::command_expr(expression_desc* ex) : e(ex)
{
	//evaluate();
}

void command_expr::evaluate()
{
	//std::cout << "e->evaluate()" << std::endl;
	e->evaluate();
	std::cout << e->get_value() << std::endl;
}

c_expression_list::c_expression_list(c_expression_list* other)
{
	unsigned int osize = other->expr_list.size();
	expr_list.resize(osize);
	for(unsigned int i=0;i<osize;i++)
	{
		expr_list[i] = other->expr_list[i];
	}
}

void c_expression_list::add(expression_desc* e)
{
	expr_list.push_back(e);
}

void c_expression_list::add(c_expression_list* other)
{
	for(unsigned int i=0;i<other->expr_list.size();i++)
	{
		expr_list.push_back(other->expr_list[i]);
	}
	//delete other???
}

int c_expression_list::return_size()
{
	return expr_list.size();
}

expression_desc* c_expression_list::return_element(unsigned int i)
{
	if (i<expr_list.size())
	{
		return expr_list[i];
	}
	else
	{
		std::cout << "ERROR: indexing error in expression_list" << std::endl;
		std::terminate();
	}
}

if_desc::if_desc(int row_number, expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_) :
row(row_number), condition(condition_), commands_pos(commands_pos_), commands_neg(commands_neg_)
{
	
}

void if_desc::evaluate()
{
	condition->evaluate();
	if(condition->get_value() == 0)
	{
		commands_neg->evaluate();
	}
	else
	{
		commands_pos->evaluate();
	}
}

while_desc::while_desc(int row_number, expression_desc* condition_, command_list_desc* commands_) :
row(row_number), loop_condition(condition_), commands(commands_) 
{}

void while_desc::evaluate()
{
	while(true)
	{
		loop_condition->evaluate();
		if (loop_condition->get_value() == 0)
		{
			break;
		}
		else
		{
			commands->evaluate();
		}
	}
}

until_desc::until_desc(int row_number, expression_desc* condition_, command_list_desc* commands_) : 
row(row_number), loop_condition(condition_), commands(commands_) 
{}

void until_desc::evaluate()
{
	while(true)
	{
		loop_condition->evaluate();
		if (loop_condition->get_value() == 1)
		{
			break;
		}
		else
		{
			commands->evaluate();
		}
	}
}
