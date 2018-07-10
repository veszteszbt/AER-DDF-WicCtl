#include "symbol_table.h"

var_value::var_value(int i) : var_type(u_integer), val(i) {}

var_value::var_value(double d) : var_type(u_double), val(d) {}

var_value::var_value(std::string* s) : var_type(u_string), val(s) {}

var_value::var_value(std::unordered_map<std::string, var_value>* a) : var_type(u_array), val(a) {}
/*template<>
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
	*stringval = s;
}

template<>
void var_value::value::set_value(std::string* s)
{
	stringval = s;
}*/

var_value::var_value() : var_type(u_integer), val(0)
{
}

var_value::~var_value()
{
	if (var_type == u_string)
	{
		//std::cout << "destroying the string: " << *(val.stringval) << std::endl;
		val.stringval->std::string::~string();
	}
	else if (var_type == u_array)
	{
		val.array->std::unordered_map<std::string, var_value>::~unordered_map();
	}
}


template<typename T>
bool var_value::value(T &t) const
{
	return false;
}

template<>
bool var_value::value(int &i) const
{
	//std::cout << "template value = " << val.intval << std::endl;
	if (var_type == u_double)
	{
		i = static_cast<int>(val.doubleval);
	}
	else if(var_type == u_string)
	{
		std::stringstream ss;
		ss << val.stringval;
		ss >> i;
		if(!ss)
			return false;
	}
	else if(var_type == u_integer)
	{
		i = val.intval;
	}
	else if(var_type == u_array)
	{
		return false;
	}
	return true;
}

template<>
bool var_value::value(double &d) const
{
	//std::cout << "template value = " << val.intval << std::endl;
	if (var_type == u_integer)
	{
		d = static_cast<double>(val.intval);
	}
	else if(var_type == u_string)
	{
		std::stringstream ss;
		ss << val.stringval;
		ss >> d;
		if(!ss)
			return false;
	}
	else if (var_type == u_double)
	{
		d = val.doubleval;
	}
	else if(var_type == u_array)
	{
		return false;
	}
	return true;
}

template<>
bool var_value::value(std::string &s) const
{
	//std::cout << "template value = " << val.intval << std::endl;
	if (var_type == u_integer)
	{
		s = std::to_string(val.intval);
	}
	else if(var_type == u_double)
	{
		s = std::to_string(val.doubleval);
	}
	else if(var_type == u_string)
	{
		s = *val.stringval;
	}
	else if(var_type == u_array)
	{
		return false;
	}
	return true;
}

template<>
bool var_value::value(std::unordered_map<std::string, var_value> &a) const
{
	if (var_type == u_array)
	{
		a = *val.array;
	}
	else
	{
		return false;
	}
	return true;
}

template<>
void var_value::set_value(int i)
{
	val.intval = i;
	//val.set_value<int>(i);
}

template<>
void var_value::set_value(double d)
{
	val.doubleval = d;
	//val.set_value<double>(d);
}

template<>
void var_value::set_value(std::string s)
{
	*(val.stringval) = s;
}

template<>
void var_value::set_value(std::string* s)
{
	val.stringval = s;
	//val.set_value<std::string*>(s);
}

template<>
void var_value::set_value(std::unordered_map<std::string, var_value>* a)
{
	val.array = a;
}

var_value::var_value(const var_value& other) : var_type(other.var_type)
{
	switch(other.var_type)
	{
		case u_integer:
		int i;
		if(other.value<int>(i))
		{
			set_value<int>(i);
		}
		else
		{
			std::cerr << "cannot convert to int" << std::endl;
		}
		//set_value<int>(other.value<int>());
		//std::cout << val.intval << " switch int " << other.value<int>() << std::endl;
		break;
		case u_double:
		double d;
		if(other.value<double>(d))
		{
			set_value<double>(d);
		}
		else
		{
			std::cerr << "cannot convert to double" << std::endl;
		}
		//set_value<double>(other.value<double>());
		break;
		case u_string:
		{ 
			std::string* temp = new std::string;
			if(other.value<std::string>(*temp))
			{
				set_value<std::string*>(temp);
			}
			else
			{
				std::cerr << "cannot convert to string" << std::endl;
			}
			break;
		}
		case u_array:
		{
			std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
			if(other.value<std::unordered_map<std::string, var_value> >(*tempmap))
			{
				set_value<std::unordered_map<std::string, var_value>*>(tempmap);
			}
			else
			{
				std::cerr << "cannot convert to array" << std::endl;
			}
			break;
		}
	}
}

void var_value::append(std::string s)
{
	if (get_type() == u_string)
	{
		std::string* temp = new std::string;
		if(value<std::string>(*temp))
		{
			(*temp).append(s);
		}
		else
		{
			std::cerr << "cannot allocate string" << std::endl;
		}
		val.stringval->std::string::~string();
		val.stringval = temp;
		//std::cout << "val append" << *(val.stringval) << std::endl;
	}
	else if(get_type() == u_integer)
	{
		var_type = u_string;
		std::string* temp = new std::string;
		int i;
		if(value<int>(i))
		{
			*temp = std::to_string(i);
		}
		else
		{
			std::cerr << "cannot convert to string" << std::endl;
		}
		(*temp).append(s);
		val.stringval = temp;
	}
	else if(get_type() == u_double)
	{
		var_type = u_string;
		std::string* temp = new std::string;
		double d;
		if(value<double>(d))
		{
			*temp = std::to_string(d);
		}
		else
		{
			std::cerr << "cannot convert to string" << std::endl;
		}
		(*temp).append(s);
		val.stringval = temp;
	}
	else if(get_type() == u_array)
	{
		std::cerr << "cannot convert array to string" << std::endl;
	}
}

bool var_value::find(std::string s)
{
	if (var_type != u_array)
	{
		std::cerr << "can't use find method since its not an array!" << std::endl;
	}
	else
	{
		auto it = val.array->find(s);
		//std::cout << "find key " << s ;
		//if (it == val.array->end())
		//{
		//	std::cout <<  " :not found" << std::endl;
		//}
		//else
		//{
		//	std::cout << " :" << it->first << ", " << it->second << std::endl;
		//}
		return (it != val.array->end());
	}
	return false;
}

std::string var_value::find_first_element_having_value(var_value v)
{
	std::string keyname;
	if (var_type != u_array)
	{
		std::cerr << "cant search for elements in a non array" << std::endl;
	}
	else
	{
		bool found = false;
		auto it = val.array->begin();
		while (it!=val.array->end() && !found)
		{
			if(it->second == v)
			{
				found = true;
				//std::cout << "find_first_element_having (-) : " << (it->first) << std::endl;
				keyname = it->first;
			}
			it++;
		}
	}
	return keyname;
}

std::vector<std::string> var_value::find_elements_having_value(var_value v)
{
	std::vector<std::string> vec;
	if (var_type != u_array)
	{
		std::cerr << "cant search for elements in a non array" << std::endl;
	}
	else
	{
		for(auto it = val.array->begin(); it != val.array->end();it++)
		{
			if (it->second == v)
			{
				//std::cout << "find_elements_having_value (/) : " << (it->first) << std::endl;
				vec.push_back(it->first);
			}
		}
	}
	return vec;
}

int var_value::get_size()
{
	if (var_type != u_array)
	{
		std::cerr << "can't get the size since its not an array!" << std::endl;
	}
	else
	{
		return val.array->size();
	}
	return 0;
}

void var_value::insert(std::string s, var_value a)
{
	if (var_type != u_array)
	{
		std::cerr << "can't insert since its not an array!" << std::endl;
	}
	else
	{
		int i = get_size();
		//std::cout << "looking up " << s << " in the map" << std::endl;
		while(find(s))
		{
			//std::cout << s << " is already an index" << std::endl;
			s = std::to_string(i);
			i++;
		}
		//std::cout << "insert function on " << s << ", " << a << std::endl;
		val.array->insert(std::pair<std::string, var_value>(s,a));
	}
}

var_value var_value::return_element_with_key(var_value v)
{
	if (var_type != u_array)
	{
		std::cerr << "can't return an element since its not an array!" << std::endl;
	}
	else
	{
		std::string s;
		if (v.get_type() == u_array)
		{
			std::cerr << "cannot use array as a key" << std::endl;
			return 0;
		}
		if(v.value<std::string>(s)){}else{std::cerr<<"cannot convert to string"<<std::endl;}

		auto it = val.array->find(s);
		if (it == val.array->end())
		{
			std::cerr << "no element found with key: " << s << std::endl;
		}
		else
		{
			return it->second;
		}
	}
	return 0;
}

std::vector<var_value> var_value::return_array_elements()
{
	std::vector<var_value> vec;
	if (var_type != u_array)
	{
		std::cerr << "can't return an element since its not an array!" << std::endl;
	}
	else
	{
		for(auto it = val.array->begin();it!=val.array->end();it++)
		{
			vec.push_back(it->second);
		}
	}
	return vec;
}

/*void var_value::delete_element_with_key(std::string key)
{
	if (get_type() != u_array)
	{
		std::cerr << "cant delete element from a non array" << std::endl;
	}
	else
	{
		if (!key.empty())
		{
			val.array->erase(key);
		}
	}
}

void var_value::delete_elements_with_key(std::vector<std::string> vec)
{
	if (get_type() != u_array)
	{
		std::cerr << "cant delete elements from a non array" << std::endl;
	}
	else
	{
		for (auto it = vec.begin();it!=vec.end();it++)
		{
			val.array->erase(it->first);
		}
	}
}*/

var_value& var_value::operator=(var_value right)
{
if (get_type() == u_array)
{
	if (right.get_type() != u_array)
	{
		std::cerr << "cant assign variable to an array" << std::endl;
	}
	else
	{
		val.array->clear();
		auto it = right.val.array->begin();
		while (it != right.val.array->end())
		{
			insert(it->first, it->second);
			it++;
		}
	}
}
else
	{
	if (right.get_type() == u_integer)
	{
		if (get_type() == u_string)
		{
			val.stringval->std::string::~string();
		}
		var_type = u_integer;
		int i;
		if (right.value<int>(i))
		{
			set_value<int>(i);
		}
		else
		{
			std::cerr << "cannot convert to int" << std::endl;
		}
	}
	else if (right.get_type() == u_double)
	{
		if (get_type() == u_string)
		{
			val.stringval->std::string::~string();
		}
		var_type = u_double;
		double d;
		if (right.value<double>(d))
		{
			set_value<double>(d);
		}
		else
		{
			std::cerr << "cannot convert to double" << std::endl;
		}
	}
	else if (right.get_type() == u_string)
	{
		if (get_type() != u_string)
		{
			std::string* temp = new std::string;
			if (right.value<std::string>(*temp)){}
			//sets pointer to temp (std::string* type)
			set_value<std::string*>(temp);
			var_type = u_string;
		}
		else
		{
			//sets the pointed string's value to the other string (std::string type)
			std::string s;
			if (right.value<std::string>(s)){}
			set_value<std::string>(s);
		}
		//std::cout << "right value string " << right.value<std::string>() << std::endl;
		//std::cout << "var_value operator =, value " << val.stringval << std::endl;
	}
	else if (right.get_type() == u_array)
	{
		if (get_type() == u_string)
		{
			val.stringval->std::string::~string();
		}
		var_type = u_array;
		std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
		if (right.value<std::unordered_map<std::string, var_value> >(*tempmap)){}
		
		set_value<std::unordered_map<std::string, var_value>*>(tempmap);

	}
}
	return *this;
}


var_value operator+(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == u_array || r.get_type() == u_array)
	{
		//std::cout << "array" << std::endl;
		ret.set_type_noconvert(u_array);
		std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
		ret.set_value<std::unordered_map<std::string,var_value>*>(tempmap);
		if (l.get_type() == u_array)
		{
			//std::cout << "a" << std::endl;
			std::unordered_map<std::string, var_value> m1;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}
			//std::cout << "b" << std::endl;
			for(auto it = m1.begin();it!=m1.end();it++)
			{
				ret.insert(it->first,it->second);
			}
			//std::cout << "c" << std::endl;
		}
		else
		{
			int i = ret.get_size();
			std::string s = std::to_string(i);
			ret.insert(s, l);
		}
		if (r.get_type() == u_array)
		{
			//std::cout << "d" << std::endl;
			std::unordered_map<std::string, var_value> m2;
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

			for(auto it = m2.begin();it!=m2.end();it++)
			{
				ret.insert(it->first,it->second);
			}
		}
		else
		{
			//std::cout << "e" << std::endl;
			int i = ret.get_size();
			std::string s = std::to_string(i);
			ret.insert(s, r);
			//std::cout << "f" << std::endl;
		}
		//ret.set_value<std::unordered_map<std::string,var_value>*>(tempmap);
		//std::cout << "g" << std::endl;
	}
	else
	{
		std::cout << "not array" << std::endl;
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = i1 + i2;
		}
		else if (l.get_type() == u_double)
		{
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = d1 + d2;
		}
		else if (l.get_type() == u_string)
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);

			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			ret.append(s1);
			ret.append(s2);
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			std::string empty = "";
			if (r.get_type() == u_integer)
			{
				ret.set_type_noconvert(u_string);
				ret.set_value<std::string*>(&empty);
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				ret.append(s1);
				ret.append(s2);
			}
			else if (r.get_type() == u_double)
			{
				ret.set_type_noconvert(u_string);
				ret.set_value<std::string*>(&empty);
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				ret.append(s1);
				ret.append(s2);
			}
		}
		else if (r.get_type()==u_string)
		{
			std::string empty = "";
			if (l.get_type() == u_integer)
			{
				ret.set_type_noconvert(u_string);
				ret.set_value<std::string*>(&empty);
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				ret.append(s1);
				ret.append(s2);
			}
			else if (l.get_type() == u_double)
			{
				ret.set_type_noconvert(u_string);
				ret.set_value<std::string*>(&empty);
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				ret.append(s1);
				ret.append(s2);
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 + d2;
			}
			else if (r.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 + d2;
			}
		}
	}
	}
	return ret;
}

var_value operator-(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == u_array || r.get_type() == u_array)
	{
		ret.set_type_noconvert(u_array);
		std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
		ret.set_value<std::unordered_map<std::string,var_value>*>(tempmap);
		if (l.get_type() == u_array)
		{
			std::unordered_map<std::string, var_value> m1;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}

			if (r.get_type() == u_array)
			{
				std::unordered_map<std::string, var_value> m2;
				if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

				for(auto it = m2.begin();it!=m2.end();it++)
				{
					std::string keyname = l.find_first_element_having_value(it->second);
					m1.erase(keyname);
				}
			}
			else
			{
				std::string keyname = l.find_first_element_having_value(r);
				m1.erase(keyname);
			}

			for(auto it = m1.begin();it!=m1.end();it++)
			{
				ret.insert(it->first,it->second);
			}
		}
		else
		{
			bool found = false;
			std::unordered_map<std::string, var_value> m2;
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}

			for(auto it = m2.begin();it!=m2.end();it++)
			{
				if (it->second == l)
				{
					found = true;
				}
			}
			
			if (!found)
			{
				int i = ret.get_size();
				std::string s = std::to_string(i);
				ret.insert(s, l);
			}
		}
	}
	else
	{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = i1 - i2;
		}
		else if (l.get_type() == u_double)
		{
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = d1 - d2;
		}
		else
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			std::size_t found = s1.find(s2);
			if (found != std::string::npos)
			{
				ret.append(s1.erase(found, s2.length()));
			}
			else
			{
				ret.append(s1);
			}
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			if (r.get_type() == u_integer)
			{	
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				if (found != std::string::npos)
				{	
					ret.append(s1.erase(found, s2.length()));
				}
				else
				{
					ret.append(s1);
				}
			}
			else if (r.get_type() == u_double)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				if (found != std::string::npos)
				{	
					ret.append(s1.erase(found, s2.length()));
				}
				else
				{
					ret.append(s1);
				}
			}
		}
		else if (r.get_type()==u_string)
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			if (l.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				if (found != std::string::npos)
				{	
					ret.append(s1.erase(found, s2.length()));
				}
				else
				{
					ret.append(s1);
				}
			}
			else if (l.get_type() == u_double)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				if (found != std::string::npos)
				{	
					ret.append(s1.erase(found, s2.length()));
				}
				else
				{
					ret.append(s1);
				}
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 - d2;
			}
			else if (r.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 - d2;
			}
		}
	}
	}
	return ret;
}

var_value operator*(var_value l, var_value r)
{
	var_value ret;
	if(l.get_type() == u_array || r.get_type() == u_array)
	{
		ret.set_type_noconvert(u_array);
		std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
		ret.set_value<std::unordered_map<std::string,var_value>*>(tempmap);

		std::cerr << "no operator * exists for arrays" << std::endl;
	}
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = i1 * i2;
		}
		else if (l.get_type() == u_double)
		{
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = d1 * d2;
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 * d2;
			}
			else if (r.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 * d2;
			}
		}
	}
	return ret;
}

var_value operator/(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == u_array || r.get_type() == u_array)
	{
		ret.set_type_noconvert(u_array);
		std::unordered_map<std::string, var_value>* tempmap = new std::unordered_map<std::string, var_value>;
		ret.set_value<std::unordered_map<std::string,var_value>*>(tempmap);
		if (l.get_type() == u_array)
		{
			std::unordered_map<std::string, var_value> m1;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}

			if (r.get_type() == u_array)
			{
				std::unordered_map<std::string, var_value> m2;
				if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

				for(auto it = m2.begin();it!=m2.end();it++)
				{
					std::vector<std::string> vec = l.find_elements_having_value(it->second);
					for(auto it2 = vec.begin();it2!=vec.end();it2++)
					{
						m1.erase(*it2);
					}
				}
			}
			else
			{
				std::vector<std::string> vec = l.find_elements_having_value(r);
				for(auto it2 = vec.begin();it2!=vec.end();it2++)
				{
					m1.erase(*it2);
				}
			}

			for(auto it = m1.begin();it!=m1.end();it++)
			{
				ret.insert(it->first,it->second);
			}
		}
		else
		{
			bool found = false;
			std::unordered_map<std::string, var_value> m2;
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}

			for(auto it = m2.begin();it!=m2.end();it++)
			{
				if (it->second == l)
				{
					found = true;
				}
			}
			
			if (!found)
			{
				int i = ret.get_size();
				std::string s = std::to_string(i);
				ret.insert(s, l);
			}
		}
	}
	else
	{
	if (r.get_type() == u_integer)
	{
		int i;
		if (r.value<int>(i))
			if (i == 0)
				throw -1;

	}
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = i1 / i2;
		}
		else if (l.get_type() == u_double)
		{
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = d1 / d2;
		}
		else
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			std::size_t found = s1.find(s2);
			while (found != std::string::npos)
			{
				s1 = (s1.erase(found, s2.length()));
				found = s1.find(s2);
			}
			ret.append(s1);
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			if (r.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				while (found != std::string::npos)
				{
					s1 = (s1.erase(found, s2.length()));
					found = s1.find(s2);
				}
				ret.append(s1);
			}
			else if (r.get_type() == u_double)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				while (found != std::string::npos)
				{
					s1 = (s1.erase(found, s2.length()));
					found = s1.find(s2);
				}
				ret.append(s1);
			}
		}
		else if (r.get_type()==u_string)
		{
			ret.set_type_noconvert(u_string);
			std::string empty = "";
			ret.set_value<std::string*>(&empty);
			if (l.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				while (found != std::string::npos)
				{
					s1 = (s1.erase(found, s2.length()));
					found = s1.find(s2);
				}
				ret.append(s1);
			}
			else if (l.get_type() == u_double)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				std::size_t found = s1.find(s2);
				while (found != std::string::npos)
				{
					s1 = (s1.erase(found, s2.length()));
					found = s1.find(s2);
				}
				ret.append(s1);
			}
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 / d2;
			}
			else if (r.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = d1 / d2;
			}
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
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = pow(i1, i2);
		}
		else if (l.get_type() == u_double)
		{
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			ret = pow(d1, d2);
		}
		else //u_string, u_array
		{
			//lehet hogy meg kéne próbálni konvertálni?
			std::cerr << "operator power only takes int or double" << std::endl;
		}
	}
	else
	{
		if (l.get_type()!=u_integer || l.get_type()!=u_double
		 || r.get_type()!=u_integer || r.get_type()!=u_double)
		{
			std::cerr << "operator power only takes int or double" << std::endl;
		}
		else
		{
			if (l.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = pow(d1, d2);
			}
			else if (r.get_type() == u_integer)
			{
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				ret = pow(d1, d2);
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
			int i1, i2;
			if (l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if (r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(i2 == 0)
			{
				throw 1;
			}
			else
			{
				ret = i1 % i2;
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

/*var_value operator++(var_value o)
{
	var_value ret;
	if (o.get_type() == u_integer)
	{
		ret = o.value<int>() + 1;
	}
	else
	{
		throw 1;
	}
	return ret;
}*/

int operator==(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
		{
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}
			
			if(i1 == i2)
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
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if (d1 == d2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_string)
		{
			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(s1 == s2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_array)
		{
			std::unordered_map<std::string, var_value> m1, m2;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}
			
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

			if(m1 == m2)
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
		if(l.get_type()==u_array || r.get_type() == u_array)
		{
			//TODO
			return 0;
		}
		else if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}

				if(r.value<std::string>(s2)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}

				if(s1 == s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}
				
				if(r.value<std::string>(s2)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}

				if(s1 == s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}
				
				if(r.value<std::string>(s2)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}

				if(s1 == s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}
				
				if(r.value<std::string>(s2)){}else{ std::cerr<<"conversion failed"<<std::endl; return 0;}

				if(s1 == s2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 == d2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 == d2)
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
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}
			
			if(i1 < i2)
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
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if (d1 < d2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_string)
		{
			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(s1 < s2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_array)
		{
			std::unordered_map<std::string, var_value> m1, m2;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}
			
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

			if(m1.size() < m2.size())
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
		if(l.get_type()==u_array || r.get_type() == u_array)
		{
			//TODO
			return 0;
		}	
		else if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 < s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 < s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 < s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 < s2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 < d2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 < d2)
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
			int i1, i2;
			if(l.value<int>(i1)){}else{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if(r.value<int>(i2)){}else{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}
			
			if(i1 > i2)
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
			double d1, d2;
			if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

			if (d1 > d2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_string)
		{
			std::string s1, s2;
			if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
			if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

			if(s1 > s2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (l.get_type() == u_array)
		{
			std::unordered_map<std::string, var_value> m1, m2;
			if(l.value<std::unordered_map<std::string, var_value> >(m1)){}else{std::cerr<<"conversion failed"<<std::endl;}
			
			if(r.value<std::unordered_map<std::string, var_value> >(m2)){}else{std::cerr<<"conversion failed"<<std::endl;}

			if(m1.size() > m2.size())
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
		if(l.get_type()==u_array || r.get_type() == u_array)
		{
			//TODO
			return 0;
		}	
		else if (l.get_type()==u_string)
		{
			if (r.get_type() == u_integer)
			{
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 > s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 > s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 > s2)
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
				std::string s1, s2;
				if(l.value<std::string>(s1)){}else{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<std::string>(s2)){}else{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

				if(s1 > s2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 > d2)
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
				double d1, d2;
				if(l.value<double>(d1)){}else{ d1 = 0; std::cerr<<"conversion failed"<<std::endl;}
				
				if(r.value<double>(d2)){}else{ d2 = 0; std::cerr<<"conversion failed"<<std::endl;}

				if(d1 > d2)
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
		//std::cout << "writing int" << std::endl;
		int i;
		if (v.value<int>(i))

		out << i;
	}
	else if (v.get_type() == u_double)
	{
		//std::cout << "writing double" << std::endl;
		double d;
		if (v.value<double>(d))

		out << d;
	}
	else if (v.get_type() == u_string)
	{
		//std::cout << "writing string" << std::endl;
		std::string s;
		if (v.value<std::string>(s))

		out << s;
	}
	else if (v.get_type() == u_array)
	{
		//TODO
		std::vector<var_value> vec = v.return_array_elements();
		auto it = vec.begin();
		out << "[ ";
		if (vec.size()!=0)
		{
			out << *it;
			it++;
			while (it!=vec.end())
			{
				out << ", " << *it;
				it++;
			}
		}
		out << " ]";
	}
	return out;
}

/*std::istream& operator>>(std::istream& in, var_value &v)
{
	v.set_value(in);
	return in; 
}*/


type var_value::get_type() const
{
	return var_type;
}

void var_value::set_type_noconvert(type t)
{
	var_type = t;
}

variable_desc::variable_desc(const variable_desc& other) : decl_row(other.decl_row), value(other.value)
{}

variable_desc& variable_desc::operator=(variable_desc right)
{
	decl_row = right.decl_row;
	value = right.value;
	return *this;
}

var_value variable_desc::return_value()
{
	return value;
}

Symbol_Table::Symbol_Table(){
	journal(journal::info, "symbol_table") << "creating symbol table" << journal::end;
	std::unordered_map<std::string, variable_desc> defaultmap;
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
	if (i == -1)
	{
		std::cerr << "variable " << name << "cannot be found" << std::endl;
		variable_desc vd(-1, var_value(0));
		return vd;
	}
	auto it = symbol_table[i].find(*name);
	return it->second;
}

void Symbol_Table::increase_stack()
{
	journal(journal::info, "symbol_table") << "increasing stack" << journal::end;
	std::unordered_map<std::string, variable_desc> pushedMap;
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