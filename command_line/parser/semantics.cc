#include "semantics.h"
#include "Parser.ih"
#include "../shell.hh"

//the commandline::shell::parser object created in main

expression_desc::expression_desc(int row_number, var_value v) : row(row_number), val(v) {}

void expression_desc::set_row(int &r)
{ row = r; }

int expression_desc::get_row()
{ return row; }

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

expression_desc::~expression_desc()
{ val.~var_value(); }

command_desc::command_desc()
{}

command_desc::command_desc(int row_number)
	: row(row_number)
{}

void command_desc::set_row(int &r)
{ row = r; }

int command_desc::get_row()
{ return row; }

command_list_desc::command_list_desc() 
	: row(0)
	, command_list(std::vector<command_desc*>())
{}

command_list_desc::command_list_desc(command_list_desc* other) 
	: row(0)
{
	unsigned int osize = other->command_list.size();
	command_list.resize(osize);
	for(unsigned int i=0;i<osize;i++)
	{
		command_list[i] = other->command_list[i];
	}
}

int command_list_desc::get_row()
{ return row; }

void command_list_desc::add(command_desc* cd)
{
	command_list.push_back(cd);
	if (commandline::shell::scanDepth == 0)
	{
		(*cd).evaluate();
	}
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

expr_binary::expr_binary() {}
expr_binary::expr_binary(int row_number, expression_desc* left, expression_desc* right)
	: row(row_number)
	, l(left)
	, r(right)
{}

expr_unary::expr_unary() {}
expr_unary::expr_unary(int row_number, expression_desc* ex)
	: row(row_number)
	, e(ex)
{}

expr_const::expr_const(int row_number, var_value v)
	: expression_desc(row_number, v)
{ val = v; }

expr_const::expr_const(int row_number) : row(row_number)
{ val.set_type_noconvert(u_null); }

void expr_const::evaluate()
{}

var_value expr_const::get_val()
{ return val; }

expr_var::expr_var(int row_number, std::string var_name) : row(row_number), name(var_name)
{}

void expr_var::evaluate()
{
	// looks up the variable in the symbol table
	int i = (*commandline::shell::parser).symbol_table.find_variable(&name);
	if (i == -1)
	{
		std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m Variable " << name << " has no value yet!" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: Variable " << name << " has no value yet!" << journal::end;
		std::terminate();
	}
	else
	{
		variable_desc v = (*commandline::shell::parser).symbol_table.get_value(&name);
		val = v.value;
		row = v.decl_row;
	}
}

var_value expr_var::get_val()
{ return val; }


expr_arr::expr_arr(int row_number,expr_arr* a) : row(row_number), val(a->get_val())
{
	//std::cout << "array init1" << std::endl;
	//val = a->get_val();
}

expr_arr::expr_arr(int row_number) : row(row_number)
{
	//std::cout << "array init2" << std::endl;
	val = new std::map<std::string, var_value>;
}

//TODO ITT BIZTOS MEMÓRIASZIVÁRGÁS LESZ
void expr_arr::deleteBecauseGccPolymorphicSucks()
{
	//std::cout << "array delete" << std::endl;
	if (val.get_type() == u_array)
	{
		val.~var_value();
	}
}

var_value expr_arr::get_val()
{ return val; }

void expr_arr::add(expression_desc* e)
{
	if (val.get_type() == u_array)
	{
		e->evaluate();
		val.insert(e->get_val());
	}
}

void expr_arr::add(expression_desc* variable, expression_desc* varvalue)
{
	if (val.get_type() == u_array)
	{
		variable->evaluate();
		varvalue->evaluate();
		var_value temp = variable->get_val();
		std::string s;
		if(temp.value(s))
			val.insert_with_overwrite(s, varvalue->get_val());

		else
		{
			std::cerr << "warning: this variable cannot be used as an index, inserting with default value" << std::endl;
			val.insert(varvalue->get_val());
		}
	}
}

void expr_arr::evaluate()
{}

assign::assign(int row_number, std::string* var_name, expression_desc* ex)
	: row(row_number), vname(var_name), e(ex)
{}

var_value assign::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (assignment)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (assignment)!" << journal::end;
	std::terminate();

	return v;
}

std::string assign::get_name()
{ return *vname; }

void assign::evaluate()
{
	e->evaluate();
	variable_desc v(row, e->get_val());

	// sets the variable named <vname> in the symbol table,
	// if it doesn't exist, it's created
	commandline::shell::parser->symbol_table.set_value(vname, v);
	journal(journal::info, "semantics") << "Assigned " << v.return_value() << " to variable name " << (*vname) << journal::end;
}

local_assign::local_assign(int row_number, std::string* var_name, expression_desc* ex)
	: row(row_number)
	, vname(var_name), e(ex)
{}

var_value local_assign::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (local assignment)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function! (local assignment)!" << journal::end;
	std::terminate();

	return v;
}

std::string local_assign::get_name()
{ return *vname; }

void local_assign::evaluate()
{
	e->evaluate();
	variable_desc v(row, e->get_val());
	//same as expr_asg
	commandline::shell::parser->symbol_table.set_local_value(vname, v);
	journal(journal::info, "semantics") << "Assigned " << v.return_value() << " to local variable name " << (*vname) << journal::end;
}

c_expression_list::c_expression_list() {}

c_expression_list::c_expression_list(c_expression_list* other)
{
	unsigned int osize = other->expr_list.size();
	expr_list.resize(osize);

	for(unsigned int i=0;i<osize;i++)
		expr_list[i] = other->expr_list[i];
}

void c_expression_list::add(expression_desc* e)
{ expr_list.push_back(e); }

void c_expression_list::add(c_expression_list* other)
{
	for(unsigned int i=0;i<other->expr_list.size();i++)
		expr_list.push_back(other->expr_list[i]);

	// delete other???
}

int c_expression_list::get_size()
{ return expr_list.size(); }

expression_desc* c_expression_list::return_element(unsigned int i)
{
	if (i<expr_list.size())
		return expr_list[i];
	else
	{
		//shouldn't happen though
		std::cerr << std::endl << "\e[31;01mERROR:\e[0m indexing error in expression_list" << std::endl;
		journal(journal::info, "semantics") << "ERROR: indexing error in expression_list" << journal::end;
		std::terminate();
	}
}

expr_par::expr_par(int row_number, expression_desc* nested)
	: row(row_number)
	, e(nested)
{}

void expr_par::evaluate()
{
	e->evaluate();
	val = e->get_val();
}

var_value expr_par::get_val()
{ return val; }

expr_ael::expr_ael(int row_number, std::string var_name, expression_desc* n)
	: row(row_number)
	, name(var_name)
	, nth(n)
{}

var_value expr_ael::get_val()
{ return val; }

void expr_ael::evaluate()
{
	// looks up the variable in the symbol table
	int i = (*commandline::shell::parser).symbol_table.find_variable(&name);
	if (i == -1)
	{
		std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m Variable " << name << " has no value yet!" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: Variable " << name << " has no value yet!" << journal::end;
		std::terminate();
	}
	else
	{
		variable_desc v = (*commandline::shell::parser).symbol_table.get_value(&name);
		var_value m = v.value;
		val = m.return_element_with_key(nth->get_val());

		row = v.decl_row;
	}
}

expr_add::expr_add(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{}

int expr_add::get_row()
{ return row; }

// type expr_add::get_type()
// { return val.get_type(); }

var_value expr_add::get_val()
{ return val; }

void expr_add::evaluate()
{
	l->evaluate();
	r->evaluate();

	// adds the values of the left and right side
	val = l->get_val() + r->get_val();
}

expr_dif::expr_dif(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{}

int expr_dif::get_row()
{ return row; }

/*type expr_dif::get_type()
{ return val.get_type(); }*/

var_value expr_dif::get_val()
{ return val; }

void expr_dif::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->get_val() - r->get_val();
}

expr_mul::expr_mul(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{}

/*type expr_mul::get_type()
{ return val.get_type(); }*/

var_value expr_mul::get_val()
{ return val; }

void expr_mul::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->get_val() * r->get_val();
}

expr_div::expr_div(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ row = row_number; }

int expr_div::get_row()
{ return row; }

var_value expr_div::get_val()
{ return val; }

void expr_div::evaluate()
{
	l->evaluate();
	r->evaluate();
	try
	{ val = l->get_val() / r->get_val(); }
	//if the r->get_val() is an int with the value 0, it'll throw -1
	catch (int)
	{
		std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m division by 0" << std::endl;
		journal(journal::info, "semantics") << row << ": ERROR: division by 0" << journal::end;
		std::terminate();
	}
}

expr_pow::expr_pow(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{}

var_value expr_pow::get_val()
{ return val; }

void expr_pow::evaluate()
{
	l->evaluate();
	r->evaluate();
	val = l->get_val() ^ r->get_val();
}

expr_mod::expr_mod(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ row = row_number; }

int expr_mod::get_row()
{ return row; }

var_value expr_mod::get_val()
{ return val; }

void expr_mod::evaluate()
{
	l->evaluate();
	r->evaluate();
	try
	{ val = l->get_val() % r->get_val(); }
	//both values must be a non-zero integer type, otherwise 1 or 2 gets thrown
	catch (int e)
	{
		switch(e)
		{
			case 1: std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m modulo cannot be 0!" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: modulo cannot be 0!" << journal::end;
					std::terminate();
					break;
			case 2: std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m modulo operator can only be used with integer type!" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: modulo operator can only be used with integer type!" << journal::end;
					std::terminate();
					break;
			default: std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m unknown error in modulo operator" << std::endl;
					journal(journal::info, "semantics") << row << ": ERROR: unknown error in modulo operator" << journal::end;
					std::terminate();
		}
	}
}

// logical operators will always return an integer value
// may be redundant
expr_or::expr_or(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_or::get_row()
{ return row; }

var_value expr_or::get_val()
{ return val; }

void expr_or::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() != 0 || r->get_val() != 0)
		val = 1;
}


expr_and::expr_and(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_and::get_row()
{ return row; }

var_value expr_and::get_val()
{ return val; }

void expr_and::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() != 0 && r->get_val() != 0)
		val = 1;
}

expr_eq::expr_eq(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_eq::get_row()
{ return row; }

var_value expr_eq::get_val()
{ return val; }

void expr_eq::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() == r->get_val())
		val = 1;
}

expr_neq::expr_neq(int row_number, expression_desc* left, expression_desc* right)
: l(left)
, r(right)
{ expr_type = u_integer; }

int expr_neq::get_row()
{ return row; }

var_value expr_neq::get_val()
{ return val; }

void expr_neq::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() != r->get_val())
		val = 1;
}

expr_leq::expr_leq(int row_number, expression_desc* left, expression_desc* right)
: l(left)
, r(right)
{ expr_type = u_integer; }

int expr_leq::get_row()
{ return row; }

var_value expr_leq::get_val()
{ return val; }

void expr_leq::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 1;
	if (l->get_val() > r->get_val())
		val = 0;
}

expr_geq::expr_geq(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_geq::get_row()
{ return row; }

var_value expr_geq::get_val()
{ return val; }

void expr_geq::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 1;
	if (l->get_val() < r->get_val())
		val = 0;
}

expr_lt::expr_lt(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_lt::get_row()
{ return row; }

var_value expr_lt::get_val()
{ return val; }

void expr_lt::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() < r->get_val())
		val = 1;
}

expr_gt::expr_gt(int row_number, expression_desc* left, expression_desc* right)
	: l(left)
	, r(right)
{ expr_type = u_integer; }

int expr_gt::get_row()
{ return row; }

var_value expr_gt::get_val()
{ return val; }

void expr_gt::evaluate()
{
	l->evaluate();
	r->evaluate();

	val = 0;
	if (l->get_val() > r->get_val())
		val = 1;
}

expr_neg::expr_neg(int row_number, expression_desc* ex)
	: e(ex)
{ expr_type = u_integer; }

int expr_neg::get_row()
{ return row; }

var_value expr_neg::get_val()
{ return val; }

void expr_neg::evaluate()
{
	e->evaluate();

	val = 1;
	if (e->get_val() != 0)
		val = 0;
}

expr_um::expr_um(int row_number, expression_desc* ex)
	: e(ex)
{}

int expr_um::get_row()
{ return row; }

var_value expr_um::get_val()
{ return val; }

void expr_um::evaluate()
{
	e->evaluate();
	expr_type = e->get_type();
	val = -1 * e->get_val(); // what happens if we unary minus a string?
}

for_3_desc::for_3_desc(
	int row_number,
	command_desc* start_,
	expression_desc* condition_,
	command_desc* iterate_,
	command_list_desc* commands_
)
	: start(start_)
	, loop_condition(condition_)
	, iterate(iterate_)
	, commands(commands_)
{ row = row_number; }

var_value for_3_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (for loop)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (for loop)!" << journal::end;
	std::terminate();

	return v;
}

void for_3_desc::evaluate()
{
	// evaluates the start condition
	start->evaluate();
	while(true)
	{
		// every loop it evaluates the condition and checks if its true
		loop_condition->evaluate();
		if (loop_condition->get_val() != 0)
		{
			commands->evaluate();
			iterate->evaluate();
		}
		else break;
	}
}

for_in_desc::for_in_desc(
	int row_number,
	std::string* variable_,
	c_expression_list* cel,
	command_list_desc* commands_
)
	: variable(variable_)
	, elements(cel)
	, commands(commands_)
{}

var_value for_in_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (for loop)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (for loop)!" << journal::end;
	std::terminate();

	return v;
}

void for_in_desc::evaluate()
{
	for(int i = 0; i < elements->get_size(); ++i)
	{
		// assigns the current element from the elements array
		assign* a = new assign(row, variable, elements->return_element(i));
		a->evaluate();
		commands->evaluate();
	}
}

if_desc::if_desc(
	int row_number,
	expression_desc* condition_,
	command_list_desc* commands_pos_,
	command_list_desc* commands_neg_
)
	: condition(condition_)
	, commands_pos(commands_pos_)
	, commands_neg(commands_neg_)
{ row = row_number; }

var_value if_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (if statement)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (if statement)!" << journal::end;
	std::terminate();

	return v;
}

void if_desc::evaluate()
{
	condition->evaluate();
	if( condition->get_val() == 0) 	//if false
		commands_neg->evaluate();
	else 							//if true
		commands_pos->evaluate();
}

while_desc::while_desc(
	int row_number,
	expression_desc* condition_,
	command_list_desc* commands_
)
	: loop_condition(condition_)
	, commands(commands_)
{ row = row_number; }

var_value while_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (while loop)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (while loop)!" << journal::end;
	std::terminate();

	return v;
}

void while_desc::evaluate()
{
	while(true)
	{
		loop_condition->evaluate();
		if (loop_condition->get_val() != 0)
			commands->evaluate();
		else
			break;
	}
}

until_desc::until_desc(
	int row_number,
	expression_desc* condition_,
	command_list_desc* commands_
)
	:  loop_condition(condition_)
	, commands(commands_)
{ row = row_number; }

var_value until_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (until loop)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (until loop)!" << journal::end;
	std::terminate();

	return v;
}

void until_desc::evaluate()
{
	while(true)
	{
		loop_condition->evaluate();
		if (loop_condition->get_val() != 0)
			break;
		else
			commands->evaluate();
	}
}

casepart::casepart(
	expression_desc* cn,
	command_list_desc* cm
)
	: condition(cn)
	, command(cm)
{}

void casepart::evaluate()
{ command->evaluate(); }

casepartvector::casepartvector() {}

void casepartvector::add(casepart* cp)
{ case_parts.push_back(cp); }

void casepartvector::add(casepartvector* other)
{
	for(unsigned int i = 0; i < other->case_parts.size(); ++i)
		case_parts.push_back(other->case_parts[i]);
}

// TODO
command_list_desc default_command_list_desc_pointer_value = command_list_desc();

case_desc::case_desc(
	int row_number,
	expression_desc* case_expr_,
	casepartvector* caseparts_,
	command_list_desc* dcase
)
	: case_expr(case_expr_)
	, case_parts(caseparts_->case_parts)
	, defaultcase(dcase)
{
	row = row_number;
	if(dcase == 0)
		dcase = &default_command_list_desc_pointer_value;
}

var_value case_desc::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function (case statement)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function (case statement)!" << journal::end;
	std::terminate();

	return v;
}

void case_desc::evaluate()
{
	case_expr->evaluate();
	bool found = false;
	for (auto it = case_parts.begin();it!=case_parts.end();it++)
	{
		(*it)->condition->evaluate();
		if (case_expr->get_val() == (*it)->condition->get_val())
		{
			found = true;
			(*it)->evaluate();
		}
	}

	if (!found)
		defaultcase->evaluate();
}

command_expr::command_expr(expression_desc* ex)
	: e(ex), result(0)
{}

var_value command_expr::get_return_value()
{ return result; }

void command_expr::evaluate()
{
	e->evaluate();
	result = e->get_val();
	// this is where the program writes the actual result you see when you run it
	std::cout << result << std::endl;
}

argumentsvector::argumentsvector()
	: is_empty(true)
{}

void argumentsvector::add(expression_desc* e)
{
	is_empty = false;
	arguments.push_back(e);
}

void argumentsvector::add(argumentsvector* other)
{
	is_empty = false;
	if ( !(other->is_empty))
	{
		for (unsigned int i = 0; i < other->arguments.size(); ++i)
		{
			arguments.push_back(other->arguments[i]);
			//also delete other here??
		}
	}
	else
		delete other;// if its the empty part, delete it -> no need to keep an empty vector of expression_descs
}

call::call(
	std::string n,
	argumentsvector* a,
	int row_number
)
	: name(n)
	, args(a->arguments)
	, returnval(0)
{ row = row_number; }

var_value call::get_return_value()
{
	evaluate();
	return returnval;
}

void call::evaluate()
{
	for(unsigned int i=0;i<args.size();i++)
		args[i]->evaluate(); //evaluate each argument's value (important)

	returnval = commandline::shell::fptr->run(this);
}

sytable_stack::sytable_stack(command_list_desc* cd)
	: c(cd)
{}

var_value sytable_stack::get_return_value()
{
	var_value v = 0;
	std::cerr << std::endl << row << ": \e[31;01mERROR:\e[0m using return value of non-returning function ( {} aka symbol table stack)!" << std::endl;
	journal(journal::info, "semantics") << row << ": ERROR: using return value of non-returning function ( {} aka symbol table stack)!" << journal::end;
	std::terminate();

	return v;
}

void sytable_stack::evaluate()
{
	// adds another symbol table for shadowing ( {} operator )
	commandline::shell::parser->symbol_table.increase_stack();
	c->evaluate();
	commandline::shell::parser->symbol_table.decrease_stack();
}
