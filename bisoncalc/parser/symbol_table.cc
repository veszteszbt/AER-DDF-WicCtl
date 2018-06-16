#include "symbol_table.h"


Symbol_Table::Symbol_Table(){
	std::map<std::string, variable_desc> defaultmap;
	symbol_table.push_back(defaultmap);
}


int Symbol_Table::find_variable(std::string* name)
{
	unsigned i = 0;
	if (symbol_table.size() < 1)
	{
		std::cerr << "ERROR: the vector of symbol tables is empty for some reason" << std::endl;
		journal(journal::info, "symbol_table") << "ERROR: the vector of symbol tables is empty for some reason" << journal::end;
		std::terminate();
	}
	while(i<symbol_table.size())
	{
		auto it = symbol_table[i].find(*name);
		if (it != symbol_table[i].end())
		{
			return i;
		}
		i++;
	}
	return -1;
}

void Symbol_Table::set_value(std::string* name, variable_desc v)
{
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

variable_desc Symbol_Table::get_value(std::string* name)
{
	int i = find_variable(name);
	//itt 2x findol, optimalizalhato
	auto it = symbol_table[i].find(*name);
	return it->second;
}

void Symbol_Table::increase_stack()
{
	std::map<std::string, variable_desc> pushedMap;
	symbol_table.push_back(pushedMap);
}

void Symbol_Table::decrease_stack()
{
	if (symbol_table.size() > 1)
	{
		symbol_table.pop_back();
	}
}