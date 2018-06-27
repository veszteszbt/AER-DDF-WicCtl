#include "semantics.h"
#include "Parser.ih"

//the parser object created in main
extern Parser* parser;

expression_desc::expression_desc(int row_number, var_value v) : row(row_number), val(v) {}

void expression_desc::set_row(int &r)
{
	row = r;
}

int expression_desc::get_row()
{
	return row;
}

type expression_desc::get_type()
{
	//ha esetleg meghívódnak nézd meg hogy jó e
	/*type temp = val.get_type();
	if (temp == u_integer)
	{
		std::cout << "u_integer" << std::endl;
	}
	else if(temp == u_double)
	{
		std::cout << "u_double" << std::endl;
	}
	else
	{
		std::cout << "u_string" << std::endl;
	}*/
	return val.get_type();
}

void command_desc::set_row(int &r)
{
	row = r;
}

int command_desc::get_row()
{
	return row;
}

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
	//delete other; a grammarban már deletelve?
}

//evaluates all the commands in the list
void command_list_desc::evaluate()
{
	for (std::vector<command_desc*>::iterator it = command_list.begin(); it != command_list.end();++it)
	{
		(*it)->evaluate();
	}
}

expr_const::expr_const(int row_number, var_value v) : 
expression_desc(row_number, v)
{
	val = v;
}

void expr_const::evaluate()
{
}

/*type expr_const::get_type()
{
	return val.get_type();
}*/

expr_var::expr_var(int row_number, std::string var_name) : row(row_number), name(var_name)
{
}

void expr_var::evaluate()
{
	//looks up the variable in the symbol table
	int i = (*parser).symbol_table.find_variable(&name);
	if (i == -1)
	{
		std::cerr << std::endl << row << ": ERROR: Variable " << name << " has no value yet!" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: Variable " << name << " has no value yet!" << journal::end;
		std::terminate();
	}
	else
	{
		variable_desc v = (*parser).symbol_table.get_value(&name);
		val = v.value;
		row = v.decl_row;
	}
}

/*type expr_var::get_type()
{
	return val.get_type();
}*/

assign::assign(int row_number, std::string* var_name, expression_desc* ex) : row(row_number), vname(var_name), e(ex)
{
}

std::string assign::get_name()
{
	return *vname;
}

void assign::evaluate()
{
	e->evaluate();
	//val = e->val;
	variable_desc v(row, e->val);
	//sets the variable named <vname> in the symbol table, if it doesn't exist, it's created
	(*parser).symbol_table.set_value(vname, v);
	journal(journal::info, "semantics") << "Assigned " << v.return_value() << " to variable name " << (*vname) << journal::end;
}

local_assign::local_assign(int row_number, std::string* var_name, expression_desc* ex) : row(row_number), vname(var_name), e(ex)
{
}

std::string local_assign::get_name()
{
	return *vname;
}

void local_assign::evaluate()
{
	e->evaluate();
	//val = e->val;
	variable_desc v(row, e->val);
	//same as expr_asg
	(*parser).symbol_table.set_local_value(vname, v);
	journal(journal::info, "semantics") << "Assigned " << v.return_value() << " to local variable name " << (*vname) << journal::end;
}

expr_par::expr_par(int row_number, expression_desc* nested) : row(row_number), e(nested)
{
}

void expr_par::evaluate()
{
	e->evaluate();
	val = e->val;
}

/*type expr_par::get_type()
{
	return val.get_type();
}*/

expr_add::expr_add(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
}

void expr_add::evaluate()
{
	l->evaluate();
	r->evaluate();
	//adds the values of the left and right side
	val = l->val + r->val;
}

int expr_add::get_row()
{
	return row;
}

/*type expr_add::get_type()
{
	return val.get_type();
}*/

expr_dif::expr_dif(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
}

void expr_dif::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->val - r->val;
}

int expr_dif::get_row()
{
	return row;
}

/*type expr_dif::get_type()
{
	return val.get_type();
}*/

expr_mul::expr_mul(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
}

void expr_mul::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->val * r->val;
}

/*type expr_mul::get_type()
{
	return val.get_type();
}*/

expr_div::expr_div(int row_number, expression_desc* left, expression_desc* right)  : row(row_number), l(left), r(right)
{
}

void expr_div::evaluate()
{
	l->evaluate();
	r->evaluate();
	try
	{
		val = l->val / r->val;
	}
	//if the r->val is an int with the value 0, it'll throw -1
	catch (int)
	{
		std::cerr << std::endl << row << ": ERROR: division by 0" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: division by 0" << journal::end;
		std::terminate();	
	}
}

int expr_div::get_row()
{
	return row;
}

/*type expr_div::get_type()
{
	return val.get_type();
}*/

expr_pow::expr_pow(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
}

void expr_pow::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->val ^ r->val;
}

/*type expr_pow::get_type()
{
	return val.get_type();
}*/

expr_mod::expr_mod(int row_number, expression_desc* left, expression_desc* right) : row(row_number), l(left), r(right)
{
}

void expr_mod::evaluate()
{
	l->evaluate();
	r->evaluate();
	try
	{
		val = l->val % r->val;
	}
	//both values must be a non-zero integer type, otherwise 1 or 2 gets thrown
	catch (int e)
	{
		switch(e)
		{
			case 1: std::cerr << std::endl << row << ": ERROR: modulo cannot be 0!" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: modulo cannot be 0!" << journal::end;
					std::terminate();
					break;
			case 2: std::cerr << std::endl << row << ": ERROR: modulo operator can only be used with integer type!" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: modulo operator can only be used with integer type!" << journal::end;
					std::terminate();
					break;
			default: std::cerr << std::endl << row << ": ERROR: unknown error in modulo operator" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: unknown error in modulo operator" << journal::end;
					std::terminate();
		}
	}
}

int expr_mod::get_row()
{
	return row;
}

/*type expr_mod::get_type()
{
	return val.get_type();
}*/

expr_or::expr_or(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	//logical operators will always return an integer value
	//may be redundant
	expr_type = u_integer;
}

void expr_or::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val != 0 || r->val != 0)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_or::get_row()
{
	return row;
}

/*type expr_or::get_type()
{
	return val.get_type();
}*/

expr_and::expr_and(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_and::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val != 0 && r->val != 0)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_and::get_row()
{
	return row;
}

/*type expr_and::get_type()
{
	return val.get_type();
}*/

expr_eq::expr_eq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_eq::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val == r->val)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_eq::get_row()
{
	return row;
}

/*type expr_eq::get_type()
{
	return val.get_type();
}*/

expr_neq::expr_neq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_neq::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val != r->val)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_neq::get_row()
{
	return row;
}

/*type expr_neq::get_type()
{
	return val.get_type();
}*/

expr_leq::expr_leq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_leq::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val > r->val)
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_leq::get_row()
{
	return row;
}

/*type expr_leq::get_type()
{
	return val.get_type();
}*/

expr_geq::expr_geq(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_geq::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val < r->val)
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_geq::get_row()
{
	return row;
}

/*type expr_geq::get_type()
{
	return val.get_type();
}*/

expr_lt::expr_lt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_lt::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val < r->val)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_lt::get_row()
{
	return row;
}

/*type expr_lt::get_type()
{
	return val.get_type();
}*/

expr_gt::expr_gt(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right)
{
	expr_type = u_integer;
}

void expr_gt::evaluate()
{
	l->evaluate();
	r->evaluate();
	if (l->val > r->val)
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
	else
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
}

int expr_gt::get_row()
{
	return row;
}

/*type expr_gt::get_type()
{
	return val.get_type();
}*/

expr_neg::expr_neg(int row_number, expression_desc* ex) : e(ex)
{
	expr_type = u_integer;
}

void expr_neg::evaluate()
{
	e->evaluate();
	if (e->val != 0)
	{
		val = 0;
		//std::cout << "FALSE" << std::endl;
	}
	else
	{
		val = 1;
		//std::cout << "TRUE" << std::endl;
	}
}

int expr_neg::get_row()
{
	return row;
}

/*type expr_neg::get_type()
{
	return val.get_type();
}*/

expr_um::expr_um(int row_number, expression_desc* ex) : e(ex)
{
}

void expr_um::evaluate()
{
	e->evaluate();
	expr_type = e->get_type();
	val = -1 * e->val; //what happens if we unary minus a string?
}

int expr_um::get_row()
{
	return row;
}

/*type expr_um::get_type()
{
	return val.get_type();
}*/

for_3_desc::for_3_desc(int row_number, command_desc* start_, expression_desc* condition_, command_desc* iterate_, command_list_desc* commands_): 
row(row_number), start(start_), loop_condition(condition_), iterate(iterate_), commands(commands_) 
{
}


void for_3_desc::evaluate()
{
	//evaluates the start condition
	start->evaluate();
	while(true)
	{
		//every loop it evaluates the condition and checks if its true
		loop_condition->evaluate();
		if (loop_condition->val == 0)
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
}

void for_in_desc::evaluate()
{
	for(int i=0;i<elements->get_size();i++)
	{
		//assigns the current element from the elements array
		assign* a = new assign(row, variable, elements->return_element(i));
		a->evaluate();
		commands->evaluate();
	}
}

command_expr::command_expr(expression_desc* ex) : e(ex)
{
}

void command_expr::evaluate()
{
	e->evaluate();
	var_value result = e->val;
	//this is where the program writes the actual result you see when you run it
	std::cout << result << std::endl;
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

int c_expression_list::get_size()
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
		//shouldn't happen though
		std::cerr << std::endl << "ERROR: indexing error in expression_list" << std::endl;
		journal(journal::info, "semantics") << "ERROR: indexing error in expression_list" << journal::end;
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
	if(condition->val == 0)
	{
		//if false
		commands_neg->evaluate();
	}
	else
	{
		//if true
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
		if (loop_condition->val == 0)
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
		if (loop_condition->val == 1)
		{
			break;
		}
		else
		{
			commands->evaluate();
		}
	}
}


casepart::casepart(expression_desc* cn, command_list_desc* cm) : condition(cn), command(cm)
{}

void casepart::evaluate()
{
	command->evaluate();
}


case_desc::case_desc(int row_number, expression_desc* case_expr_, casepartvector* caseparts_, command_list_desc* dcase) :
row(row_number), case_expr(case_expr_), case_parts(caseparts_->case_parts), defaultcase(dcase)
{}


void case_desc::evaluate()
{
	case_expr->evaluate();
	auto it = case_parts.begin();
	bool found = false;
	while (it!=case_parts.end() && found == false)
	{
		(*it)->condition->evaluate();
		if (case_expr->val == ((*it)->condition->val))
		{
			found = true;
			(*it)->evaluate();
		}
		it++;
	}
	if (!found)
	{
		defaultcase->evaluate();
	}
}

casepartvector::casepartvector(){}

void casepartvector::add(casepart* cp)
{
	case_parts.push_back(cp);
}

void casepartvector::add(casepartvector* other)
{
	for(unsigned int i=0;i<other->case_parts.size();i++)
	{
		case_parts.push_back(other->case_parts[i]);
	}
}

call::call(std::string n, argumentsvector* a) : name(n), args(a->arguments){}

void call::evaluate()
{
	std::cout << "call name: " << name << std::endl << "args:";
	for(unsigned int i=0;i<args.size();i++)
	{
		args[i]->evaluate(); //evaluate each argument's value (important)
		std::cout << " " << args[i]->val;
	}
	std::cout << std::endl;
}

argumentsvector::argumentsvector() : is_empty(true){}

void argumentsvector::add(expression_desc* e)
{
	is_empty = false;
	arguments.push_back(e);
}

void argumentsvector::add(argumentsvector* other)
{
	is_empty = false;
	if (!(other->is_empty))
	{
		for (unsigned int i=0;i<other->arguments.size();i++)
		{
			arguments.push_back(other->arguments[i]);
			//also delete other here??
		}
	}
	else
	{
		delete other;// if its the empty part, delete it
		//no need to keep an empty vector of expression_descs
	}
}

sytable_stack::sytable_stack(command_list_desc* cd) : c(cd)
{}

void sytable_stack::evaluate()
{
	//adds another symbol table for shadowing ( {} operator ) 
	(*parser).symbol_table.increase_stack();
	c->evaluate();
	(*parser).symbol_table.decrease_stack();
}
