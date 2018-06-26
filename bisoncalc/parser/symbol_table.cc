#include "symbol_table.h"

/*value& var_value::value::operator=(value right)
{
	intval = right.intval;
	return *this;
}*/

var_value::var_value(int i) : var_type(u_integer), val(i) {}

var_value::var_value(double d) : var_type(u_double), val(d) {}

var_value::var_value(std::string s) : var_type(u_string), val(s) {}

template<>
void var_value::value::set_value(int i)
{
	intval = i;
}

template<>
void var_value::value::set_value(double d)
{
	doubleval = d;
}

template<>
void var_value::value::set_value(std::string s)
{
	stringval = s;
}

var_value::var_value() : var_type(u_integer), val(0)
{
	//std::cout << "var_value default const" << std::endl;
}

var_value::~var_value()
{
	if (var_type == u_string)
	{
		val.stringval.std::string::~string();
	}
}

template<>
int var_value::value() const
{
	//std::cout << "template value = " << val.intval << std::endl;
	return val.intval;
}

template<>
double var_value::value() const
{
	//std::cout << "template value = " << val.doubleval << std::endl;
	return val.doubleval;
}

template<>
std::string var_value::value() const
{
	//std::cout << "template value = " << val.stringval << std::endl;
	return val.stringval;
}

template<>
void var_value::value(int i)
{
	val.intval = i;
}

template<>
void var_value::value(double d)
{
	val.doubleval = d;
}

template<>
void var_value::value(std::string s)
{
	val.stringval = s;
}

var_value::var_value(const var_value& other) : var_type(other.var_type)
{
	switch(other.var_type)
	{
		case u_integer: val.set_value(other.value<int>());
		//std::cout << val.intval << " switch int " << other.value<int>() << std::endl;
		break;
		case u_double: val.set_value(other.value<double>());
		break;
		case u_string: val.set_value(other.value<std::string>());
		break;
	}
}

var_value& var_value::operator=(var_value right)
{
	if (right.get_type() == u_integer)
	{
		var_type = u_integer;
		this->val.set_value(right.value<int>());
		//std::cout << "right value int " << right.value<int>() << std::endl;
		//std::cout << "var_value operator =, value " << val.intval << std::endl;
	}
	else if (right.get_type() == u_double)
	{
		var_type = u_double;
		this->val.set_value(right.value<double>());
		//std::cout << "right value double " << right.value<double>() << std::endl;
		//std::cout << "var_value operator =, value " << val.doubleval << std::endl;
	}
	else 
	{
		var_type = u_string;
		this->val.set_value(right.value<std::string>());
		//std::cout << "right value string " << right.value<std::string>() << std::endl;
		//std::cout << "var_value operator =, value " << val.stringval << std::endl;
	}
	return *this;
}

var_value operator+(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			ret = l.value<int>() + r.value<int>();
		}
		else if (l.get_type() == u_double)
		{
			ret = l.value<double>() + r.value<double>();
		}
		else
		{
			ret = l.value<std::string>() + r.value<std::string>();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				ret = l.value<std::string>() + std::to_string(r.value<int>());
			}
			else if (r.get_type() == u_double)
			{
				ret = l.value<std::string>() + std::to_string(r.value<double>());
			}
		}
		else if (r.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				ret = std::to_string(l.value<int>()) + r.value<std::string>();
			}
			else if (r.get_type() == u_double)
			{
				ret = std::to_string(l.value<double>()) + r.value<std::string>();
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				ret = static_cast<double>(l.value<int>()) + r.value<double>();
			}
			else if (r.get_type() == u_integer)
			{
				ret = static_cast<double>(r.value<int>()) + l.value<double>();
			}
		}
	}
	return ret;
}

var_value operator-(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			ret = l.value<int>() - r.value<int>();
		}
		else if (l.get_type() == u_double)
		{
			ret = l.value<double>() - r.value<double>();
		}
		else
		{
			//ret.value<std::string> += l.value<std::string>();
			//ret.value<std::string> += r.value<std::string>();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (r.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(r.value<int>());
			}
			else if (r.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(r.value<double>());
			}
		}
		else if (r.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (l.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(l.value<int>());
			}
			else if (l.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(l.value<double>());
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				ret = static_cast<double>(l.value<int>()) - r.value<double>();
			}
			else if (r.get_type() == u_integer)
			{
				ret =  l.value<double>() - static_cast<double>(r.value<int>());
			}
		}
	}
	return ret;
}

var_value operator*(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			ret = l.value<int>() * r.value<int>();
		}
		else if (l.get_type() == u_double)
		{
			ret = l.value<double>() * r.value<double>();
		}
		else
		{
			//ret.value<std::string> += l.value<std::string>();
			//ret.value<std::string> += r.value<std::string>();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (r.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(r.value<int>());
			}
			else if (r.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(r.value<double>());
			}
		}
		else if (r.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (l.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(l.value<int>());
			}
			else if (l.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(l.value<double>());
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				ret = static_cast<double>(l.value<int>()) * r.value<double>();
			}
			else if (r.get_type() == u_integer)
			{
				ret = static_cast<double>(r.value<int>()) * l.value<double>();
			}
		}
	}
	return ret;
}

var_value operator/(var_value l, var_value r)
{
	if (r.get_type() == u_integer)
	{
		if (r.value<int>() == 0)
		{
			throw -1;
		}
	}
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			ret = static_cast<double>(l.value<int>()) / static_cast<double>(r.value<int>());
		}
		else if (l.get_type() == u_double)
		{
			ret = l.value<double>() / r.value<double>();
		}
		else
		{
			//ret.value<std::string> += l.value<std::string>();
			//ret.value<std::string> += r.value<std::string>();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (r.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(r.value<int>());
			}
			else if (r.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(r.value<double>());
			}
		}
		else if (r.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (l.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(l.value<int>());
			}
			else if (l.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(l.value<double>());
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				ret = static_cast<double>(l.value<int>()) / r.value<double>();
			}
			else if (r.get_type() == u_integer)
			{
				ret = l.value<double>() / static_cast<double>(r.value<int>());
			}
		}
	}
	return ret;
}

var_value operator^(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			ret = pow(l.value<int>(), r.value<int>());
		}
		else if (l.get_type() == u_double)
		{
			ret = pow(l.value<double>(), r.value<double>());
		}
		else
		{
			//ret.value<std::string> += l.value<std::string>();
			//ret.value<std::string> += r.value<std::string>();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (r.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(r.value<int>());
			}
			else if (r.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(r.value<double>());
			}
		}
		else if (r.get_type()==u_string)
		{
			//ret.value<std::string> +=l.value<std::string>();
			if (l.get_type() == u_integer)
			{
				//ret.value<std::string> +=std::to_string(l.value<int>());
			}
			else if (l.get_type() == u_double)
			{
				//ret.value<std::string> +=std::to_string(l.value<double>());
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				ret = pow(static_cast<double>(l.value<int>()), r.value<double>());
			}
			else if (r.get_type() == u_integer)
			{
				ret = pow(l.value<double>(), static_cast<double>(r.value<int>()));
			}
		}
	}
	return ret;
}

var_value operator%(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			if (r.value<int>() == 0)
			{
				throw 1;
			}
			else
			{
				ret = l.value<int>() % r.value<int>();
			}
		}
		else
		{
			throw 2;
		} 
	}
	else
	{
	 	throw 2;
	}
	return ret;
}

int operator==(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			if(l.value<int>() == r.value<int>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_double)
		{
			if(l.value<double>() == r.value<double>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(l.value<std::string>() == r.value<std::string>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				if(l.value<std::string>() == std::to_string(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_double)
			{
				if(l.value<std::string>() == std::to_string(r.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else if (r.get_type()==u_string)
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<std::string>() == std::to_string(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (l.get_type() == u_double)
			{
				if(r.value<std::string>() == std::to_string(l.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<double>() == static_cast<double>(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_integer)
			{
				if(l.value<double>() == static_cast<double>(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	return -1; //just to get rid of the warning
}

int operator!=(var_value l, var_value r)
{
	if (l == r)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int operator<(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			if(l.value<int>() < r.value<int>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_double)
		{
			if(l.value<double>() < r.value<double>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(l.value<std::string>() < r.value<std::string>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				if(l.value<std::string>() < std::to_string(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_double)
			{
				if(l.value<std::string>() < std::to_string(r.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else if (r.get_type()==u_string)
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<std::string>() < std::to_string(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (l.get_type() == u_double)
			{
				if(r.value<std::string>() < std::to_string(l.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<double>() < static_cast<double>(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_integer)
			{
				if(l.value<double>() < static_cast<double>(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	return -1; //just to get rid of the warning
}

int operator>(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			if(l.value<int>() > r.value<int>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_double)
		{
			if(l.value<double>() > r.value<double>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(l.value<std::string>() > r.value<std::string>())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				if(l.value<std::string>() > std::to_string(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_double)
			{
				if(l.value<std::string>() > std::to_string(r.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else if (r.get_type()==u_string)
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<std::string>() > std::to_string(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (l.get_type() == u_double)
			{
				if(r.value<std::string>() > std::to_string(l.value<double>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				if(r.value<double>() > static_cast<double>(l.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (r.get_type() == u_integer)
			{
				if(l.value<double>() > static_cast<double>(r.value<int>()))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	return -1; //just to get rid of the warning
}

int operator>=(var_value l, var_value r)
{
	if (l < r)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int operator<=(var_value l, var_value r)
{
	if (l > r)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

std::ostream& operator<<(std::ostream& out, var_value &v)
{
	if (v.get_type() == u_integer)
	{
		out << v.value<int>();
	}
	else if (v.get_type() == u_double)
	{
		out << v.value<double>();
	}
	else
	{
		out << v.value<std::string>();
	}
	return out;
}

/*std::istream& operator>>(std::istream& in, var_value &v)
{
	v.set_value(in);
	return in; 
}*/


type var_value::get_type()
{
	return var_type;
}

variable_desc::variable_desc(const variable_desc& other) : decl_row(other.decl_row), value(other.value)
{}

variable_desc& variable_desc::operator=(variable_desc right)
{
	decl_row = right.decl_row;
	value = right.value;
	return *this;
}

int variable_desc::return_intval()
{
	return value.value<int>();
}

double variable_desc::return_doubleval()
{
	return value.value<double>();
}

std::string variable_desc::return_stringval()
{
	return value.value<std::string>();
}

Symbol_Table::Symbol_Table(){
	journal(journal::info, "symbol_table") << "creating symbol table" << journal::end;
	std::map<std::string, variable_desc> defaultmap;
	symbol_table.push_back(defaultmap);
}


int Symbol_Table::find_variable(std::string* name)
{
	unsigned i = symbol_table.size();
	if (symbol_table.size() < 1)
	{
		std::cerr << "ERROR: the vector of symbol tables is empty for some reason" << std::endl;
		journal(journal::info, "symbol_table") << "ERROR: the vector of symbol tables is empty for some reason" << journal::end;
		std::terminate();
	}
	while(i>0)
	{
		i--;
		auto it = symbol_table[i].find(*name);
		if (it != symbol_table[i].end())
		{
			return i;
		}
	}
	return -1;
}

void Symbol_Table::set_value(std::string* name, variable_desc v)
{
	journal(journal::info, "symbol_table") << "set value of " << *name << journal::end;
	int i = find_variable(name);
	if (i != -1)
	{
		symbol_table[i][*name] = v;
	}
	else
	{
		int j = symbol_table.size();
		symbol_table[j-1][*name] = v;
	}
}

void Symbol_Table::set_local_value(std::string* name, variable_desc v)
{
	journal(journal::info, "symbol_table") << "set local value of " << *name << journal::end;
	int j = symbol_table.size();
	symbol_table[j-1][*name] = v;
}

variable_desc Symbol_Table::get_value(std::string* name)
{
	journal(journal::info, "symbol_table") << "get value of " << *name << journal::end;
	int i = find_variable(name);
	//itt 2x findol, optimalizalhato
	auto it = symbol_table[i].find(*name);
	return it->second;
}

void Symbol_Table::increase_stack()
{
	journal(journal::info, "symbol_table") << "increasing stack" << journal::end;
	std::map<std::string, variable_desc> pushedMap;
	symbol_table.push_back(pushedMap);
}

void Symbol_Table::decrease_stack()
{
	journal(journal::info, "symbol_table") << "decreasing stack" << journal::end;
	if (symbol_table.size() > 1)
	{
		symbol_table.pop_back();
	}
}