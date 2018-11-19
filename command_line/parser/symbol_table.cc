#include "symbol_table.h"


void s_minus(const var_value& lhs, const var_value& rhs, var_value& ret)
{
	ret.set_type_noconvert(u_string);

	std::string empty = "";
	ret.set_value(&empty);

	std::string s1, s2;
	if( !lhs.value(s1))
	{ s1 = ""; std::cerr<<"conversion failed"<<std::endl;}

	if( !rhs.value(s2))
	{ s2 = ""; std::cerr<<"conversion failed"<<std::endl;}

	std::size_t found = s1.find(s2);
	if (found != std::string::npos)
		ret.append(s1.erase(found, s2.length()));
	else
		ret.append(s1);
}

void s_add(const var_value& lhs, const var_value& rhs, var_value& ret)
{
	ret.set_type_noconvert(u_string);

	std::string empty = "";
	ret.set_value(&empty);

	std::string s1, s2;
	if(!lhs.value(s1))
	{ s1 = ""; std::cerr<<"conversion failed"<<std::endl; }

	if(!rhs.value(s2))
	{ s2 = ""; std::cerr<<"conversion failed"<<std::endl; }

	ret.append(s1);
	ret.append(s2);
}

void s_div(const var_value& lhs, const var_value& rhs, var_value& ret)
{
	ret.set_type_noconvert(u_string);

	std::string empty = "";
	ret.set_value(&empty);

	std::string s1, s2;
	if(!lhs.value(s1))
	{ s1 = ""; std::cerr<<"conversion failed"<<std::endl; }

	if(!rhs.value(s2))
	{ s2 = ""; std::cerr<<"conversion failed"<<std::endl; }

	std::size_t found = s1.find(s2);
	while (found != std::string::npos)
	{
		s1 = (s1.erase(found, s2.length()));
		found = s1.find(s2);
	}
	ret.append(s1);
}

template <typename T>
struct mul
{
	constexpr static T calculate(const T& lhs, const T& rhs)
	{ return lhs * rhs; }
};

template <typename T>
struct division
{
	constexpr static T calculate(const T& lhs, const T& rhs)
	{ return lhs / rhs; }
};

template <typename T>
struct minus
{
	constexpr static T calculate(const T& lhs, const T& rhs)
	{ return lhs - rhs; }
};

template <typename T>
struct add
{
	constexpr static T calculate(const T& lhs, const T& rhs)
	{ return lhs + rhs; }
};

template <typename T>
struct power
{
	constexpr static T calculate(const T& lhs, const T& rhs)
	{ return pow(lhs, rhs); }
};

template <template<typename> typename Op, typename T>
std::enable_if_t<types::meta::is_one_of_v<T, int, double>, T>
op(const var_value& lhs, const var_value& rhs)
{
	T i1, i2;
	if(!lhs.value(i1))
	{ i1 = 0; std::cerr<<"conversion failed"<<std::endl;}

	if(!rhs.value(i2))
	{ i2 = 0; std::cerr<<"conversion failed"<<std::endl;}

	return Op<T>::calculate(i1, i2);
}

var_value::var_value(int i)
	: var_type(u_integer)
	, val(i)
{}

var_value::var_value(double d)
	: var_type(u_double)
	, val(d)
{}

var_value::var_value(std::string* s)
	: var_type(u_string)
	, val(s)
{}

var_value::var_value(arraypair* a)
	: var_type(u_array)
	, val(a)
{}

var_value::var_value()
	: var_type(u_integer)
	, val(0)
{}

var_value::~var_value()
{
	if (var_type == u_string)
		val.stringval->std::string::~string();
	else if (var_type == u_array)
		val.array->arraypair::~map();
}


//value() function attempts to convert and put the current value of the variable into the parameter variable
bool var_value::value(int &i) const
{
	if (var_type == u_double)
		i = static_cast<int>(val.doubleval);
	else if(var_type == u_string)
	{
		std::stringstream ss;
		ss << val.stringval;
		ss >> i;
		if(!ss)
			return false;
	}
	else if(var_type == u_integer)
		i = val.intval;
	else if(var_type == u_array)
		return false;

	return true;
}

bool var_value::value(bool &b) const
{
	if (var_type == u_double)
		b = static_cast<int>(val.doubleval);
	else if(var_type == u_string)
	{
		std::stringstream ss;
		ss << val.stringval;
		ss >> b;
		if(!ss)
			return false;
	}
	else if(var_type == u_integer)
		b = val.intval;
	else if(var_type == u_array)
		return false;

	return true;
}


bool var_value::value(double &d) const
{
	if (var_type == u_integer)
	{ d = static_cast<double>(val.intval); }
	else if(var_type == u_string)
	{
		std::stringstream ss;
		ss << val.stringval;
		ss >> d;
		if(!ss)
			return false;
	}
	else if (var_type == u_double)
		d = val.doubleval;
	else if(var_type == u_array)
		return false;

	return true;
}

bool var_value::value(std::string &s) const
{
	if (var_type == u_integer)
		s = std::to_string(val.intval);
	else if(var_type == u_double)
		s = std::to_string(val.doubleval);
	else if(var_type == u_string)
		s = *val.stringval;
	else if(var_type == u_array)
		return false;

	return true;
}

bool var_value::value(arraypair &a) const
{
	if (var_type == u_array)
		a = *val.array;
	else
		return false;

	return true;
}

void var_value::set_value(int i)
{ val.intval = i; }

void var_value::set_value(double d)
{ val.doubleval = d; }

void var_value::set_value(std::string& s)
{ *(val.stringval) = s; }

void var_value::set_value(std::string* s)
{ val.stringval = s; }

void var_value::set_value(arraypair* a)
{ val.array = a; }

var_value::var_value(const var_value& other) : var_type(other.var_type)
{
	switch(other.var_type)
	{
		case u_integer:
		{
			int i;
			if(other.value(i))
			{
				set_value(i);
				var_type = u_integer;
			}
			else
				std::cerr << "cannot convert to int" << std::endl;

			break;
		}
		case u_double:
		{
			double d;
			if(other.value(d))
			{
				set_value(d);
				var_type = u_double;
			}
			else
				std::cerr << "cannot convert to double" << std::endl;

			break;
		}
		case u_string:
		{
			std::string* temp = new std::string;
			if(other.value(*temp))
			{
				set_value(temp);
				var_type = u_string;
			}
			else
				std::cerr << "cannot convert to string" << std::endl;

			break;
		}
		case u_array:
		{
			arraypair* tempmap = new arraypair;
			if(other.value(*tempmap))
			{
				set_value(tempmap);
				var_type = u_array;
			}
			else
				std::cerr << "cannot convert to array" << std::endl;

			break;
		}
		case u_null:
			var_type = u_null;
	}
}

void var_value::append(std::string s)
{
	if (get_type() == u_string)
	{
		std::string* temp = new std::string;
		if(value(*temp))
			temp->append(s);
		else
			std::cerr << "cannot allocate string" << std::endl;

		val.stringval->std::string::~string();
		val.stringval = temp;
	}
	else if(get_type() == u_integer)
	{
		var_type = u_string;
		std::string* temp = new std::string;
		int i;
		if(value(i))
			*temp = std::to_string(i);

		else
			std::cerr << "cannot convert to string" << std::endl;

		temp->append(s);
		val.stringval = temp;
	}
	else if(get_type() == u_double)
	{
		var_type = u_string;
		std::string* temp = new std::string;
		double d;
		if(value(d))
			*temp = std::to_string(d);

		else
			std::cerr << "cannot convert to string" << std::endl;

		temp->append(s);
		val.stringval = temp;
	}
	else if(get_type() == u_array)
		std::cerr << "cannot convert array to string" << std::endl;
}

std::pair<bool, arraypair::iterator>
var_value::exists_in_array(std::string s)
{
	if (var_type != u_array)
		std::cerr << "can't use exists_in_array method since its not an array!" << std::endl;

	else
	{
		auto it = val.array->find(s);
		return std::make_pair(it != val.array->end(), it);
	}

	return std::make_pair(false, arraypair().end());
}

std::string var_value::find_first_element_having_value(var_value v)
{
	std::string keyname;
	if (var_type != u_array)
		std::cerr << "cant search for elements in a non array" << std::endl;

	else
	{
		bool found = false;
		auto it = val.array->cbegin();
		while (it!=val.array->cend() && !found)
		{
			if(it->second == v)
			{
				found = true;
				keyname = it->first;
			}
			++it;
		}
	}
	return keyname;
}

std::string var_value::find_last_element_having_value(var_value v)
{
	std::string keyname;
	if (var_type != u_array)
		std::cerr << "cant search for elements in a non array" << std::endl;

	else
	{
		bool found = false;
		auto it = val.array->crbegin();
		while (it!=val.array->crend() && !found)
		{
			if(it->second == v)
			{
				found = true;
				keyname = it->first;
			}
			++it;
		}
	}

	return keyname;
}

std::vector<std::string> var_value::find_elements_having_value(var_value v)
{
	std::vector<std::string> vec;
	if (var_type != u_array)
		std::cerr << "cant search for elements in a non array" << std::endl;

	else
	{
		for(auto it = val.array->begin(); it != val.array->end();it++)
			if (it->second == v)
				vec.push_back(it->first);
	}
	return vec;
}

int var_value::get_size()
{
	if (var_type != u_array)
		std::cerr << "can't get the size since its not an array!" << std::endl;

	else
		return val.array->size();

	return 0;
}

void var_value::insert(const var_value &a)
{ insert_after_max(a); }

struct get_max
{
	int operator()(var_value &obj)
	{ return obj.getMaxKey() + 1; }
};

struct get_min
{
	int operator()(var_value &obj)
	{ return obj.getMinKey() - 1; }
};

template <typename Op>
void var_value::insert_impl(const var_value &a)
{
	if (var_type != u_array)
		std::cerr << "can't insert since its not an array!" << std::endl;

	else
	{
		int i = Op()(*this);
		std::string s = std::to_string(i);
		val.array->emplace(s, a);
	}
}

void var_value::insert_after_max(const var_value &a)
{ insert_impl< get_max >(a); }

void var_value::insert_before_min(const var_value &a)
{ insert_impl< get_min >(a); }

void var_value::insert(std::string s, const var_value &a)
{
	if (var_type != u_array)
		std::cerr << "can't insert since its not an array!" << std::endl;

	else
	{
		if (exists_in_array(s).first)
		{
			int i = getMaxKey() + 1;
			s = std::to_string(i);
		}
		val.array->emplace(s,a);
	}
}

void var_value::insert_with_add(const std::string &s, const var_value &a)
{ insert_with_impl<add<var_value>>(s, a); }

void var_value::insert_with_dif(const std::string &s, const var_value &a)
{ insert_with_impl<minus<var_value>>(s, a); }

/*
template <typename Top>
void insert_with_impl()
{
	if (var_type != u_array)
	{ std::cerr << "can't insert since its not an array!" << std::endl; }
	else
	{
		bool exists;
		arraypair::iterator it;
		std::tie(exists, it) = exists_in_array(s);
		if (exists)
			it->second = Top::calculate(it->second, a);
		else
			insert(s, a);
	}
}
*/

void var_value::insert_with_overwrite(const std::string &s, var_value a)
{
	bool exists;
	arraypair::iterator it;
	std::tie(exists, it) = exists_in_array(s);
	if (exists)
		it->second = a;

	else
		insert(s, a);
}

var_value var_value::return_element_with_key(var_value v)
{
	if (var_type != u_array)
		std::cerr << "can't return an element since its not an array!" << std::endl;

	else
	{
		std::string s;
		if (v.get_type() == u_array)
		{
			std::cerr << "cannot use array as a key" << std::endl;
			return 0;
		}
		if( !v.value(s))
		{ std::cerr<<"cannot convert to string"<<std::endl; }

		auto it = val.array->find(s);
		if (it == val.array->end())
			std::cerr << "no element found with key: " << s << std::endl;

		else
			return it->second;
	}
	return 0;
}

std::vector<var_value> var_value::return_array_elements()
{
	std::vector<var_value> vec;
	if (var_type != u_array)
		std::cerr << "can't return an element since its not an array!" << std::endl;

	else
	{
		for(auto it = val.array->begin(); it != val.array->end(); ++it)
			vec.push_back(it->second);
	}
	return vec;
}

void delete_from_arraypair(arraypair &a, const std::string &k)
{ a.erase(k); }

int var_value::getMaxKey()
{ return get_boundary_value_key_impl(val.array->crbegin(), val.array->crend()); }

int var_value::getMinKey()
{ return get_boundary_value_key_impl(val.array->cbegin(), val.array->cend()); }

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

template <typename Ttype>
std::enable_if_t< types::meta::is_one_of_v<Ttype, int, double>, void >
var_value::assign_impl(const type &t, var_value right)
{
	if (get_type() == u_string)
		val.stringval->std::string::~string();

	var_type = t;

	Ttype i;
	if (right.value(i))
		set_value(i);

	else
		std::cerr << "cannot convert to int" << std::endl;
}

var_value& var_value::operator=(var_value right)
{
	if (get_type() == u_array)
	{
		if (right.get_type() != u_array)
		{
			val.array->arraypair::~map();
			if (right.get_type() == u_string)
			{
				std::string* temp = new std::string;
				right.value(*temp);
				// sets pointer to temp (std::string* type)
				set_value(temp);
				var_type = u_string;
			}
			else if (right.get_type() == u_integer)
				assign_impl<int>(u_integer, right);

			else if (right.get_type() == u_double)
				assign_impl<double>(u_double, right);
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
			assign_impl<int>(u_integer, right);

		else if (right.get_type() == u_double)
			assign_impl<double>(u_double, right);

		// TODO atnezni
		else if (right.get_type() == u_string)
		{
			if (get_type() != u_string)
			{
				std::string* temp = new std::string;
				right.value(*temp);
				// sets pointer to temp (std::string* type)
				set_value(temp);
				var_type = u_string;
			}
			else
			{
				// sets the pointed string's value to the other string (std::string type)
				std::string s;
				right.value(s);
				set_value(s);
			}
		}
		else if (right.get_type() == u_array)
		{
			if (get_type() == u_string)
				val.stringval->std::string::~string();

			var_type = u_array;
			arraypair* tempmap = new arraypair;
			right.value(*tempmap);

			set_value(tempmap);
		}
	}
	return *this;
}

void var_value::unio(const arraypair& b)
{
    auto in1 = val.array->begin();
    auto in2 = b.begin();

    while(in1 != val.array->end() || in2 != b.end())
    {
        if( in2 == b.end() || (
               in1 != val.array->end() &&
               in1->first < in2->first
        ))
        { ++in1; }
        else
        if( in1 == val.array->end() || (
                in2 != b.end() &&
                in2->first < in1->first
        ))
        {
            val.array->emplace(in2->first, in2->second);
            ++in2;
        }
        else //in1->first == in2->first
        {
            in1->second = in1->second + in2->second;
            ++in1;
            ++in2;
        }
    }
}

var_value operator+(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == u_array || r.get_type() == u_array)
	{
		ret.set_type_noconvert(u_array);
		arraypair* tempmap = new arraypair;
		ret.set_value(tempmap);

		if (l.get_type() == u_array && r.get_type() != u_array)
		{
			if(!l.value(*tempmap))
			{ std::cerr<<"conversion failed"<<std::endl; }

			ret.insert_after_max(r);
		}
		else if (r.get_type() == u_array && l.get_type() != u_array)
		{
			if(!r.value(*tempmap))
			{ std::cerr<<"conversion failed"<<std::endl; }

			ret.insert_before_min(l);
		}
		else if (l.get_type() == u_array && r.get_type() == u_array)
		{
			if(!l.value(*tempmap))
			{ std::cerr<<"conversion failed"<<std::endl; }

			ret.unio(*r.val.array);
		}
	}
	else
	{
		if (l.get_type() == r.get_type())
		{
			if (l.get_type() == u_integer)
				ret = op<add, int>(l, r);
			else if (l.get_type() == u_double)
				ret = op<add, double>(l, r);
			else if (l.get_type() == u_string)
				s_add(l, r, ret);
		}
		else
		{
			if (l.get_type() == u_string || r.get_type() == u_string)
			{
				if (r.get_type() == u_integer ||
					r.get_type() == u_double  ||
					l.get_type() == u_integer ||
					l.get_type() == u_double
				) { s_add(l, r, ret); }
			}
			else if (l.get_type() == u_double || r.get_type() == u_double)
			{
				if (l.get_type() == u_integer || r.get_type() == u_integer)
					ret = op<add, double>(l, r);
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
		arraypair* tempmap = new arraypair;
		ret.set_value(tempmap);
		if (l.get_type() == u_array)
		{
			arraypair m1;
			if(!l.value(m1))
			{ std::cerr<<"conversion failed"<<std::endl; }

			//TODO make it ordo n + m
			for(auto it = m1.begin(); it != m1.end(); ++it)
				ret.insert(it->first,it->second);

			if (r.get_type() == u_array)
			{
				arraypair m2;
				if(!r.value(m2))
				{ std::cerr<<"conversion failed"<<std::endl; }

				for(auto it = m2.begin();it!=m2.end();it++)
					ret.insert_with_dif(it->first, it->second);
			}
			else
			{
				const std::string keyname = l.find_first_element_having_value(r);
				ret.val.array->erase(keyname);
			}
		}
		else
		{
			arraypair m2;
			if(!r.value(m2))
			{ std::cerr<<"conversion failed"<<std::endl; }

			for(auto it = m2.begin();it!=m2.end();it++)
				ret.insert(it->first, it->second);

			std::string keyname = r.find_last_element_having_value(l);
			ret.val.array->erase(keyname);
		}
	}
	else
	{
		if (l.get_type() == r.get_type())
		{
			if (l.get_type() == u_integer)
				ret = op<minus, int>(l, r);
			else if (l.get_type() == u_double)
				ret = op<minus, double>(l, r);
			else
				s_minus(l, r, ret);
		}
		else
		{
			if (l.get_type() == u_string || r.get_type() == u_string)
			{
				if (r.get_type() == u_integer ||
					r.get_type() == u_double  ||
					l.get_type() == u_integer ||
					l.get_type() == u_double
				) { s_minus(l, r, ret); }
				else if (r.get_type() == u_array)
				{
					//TODO
				}
			}
			else if (l.get_type() == u_double || r.get_type() == u_double)
				if (l.get_type() == u_integer || r.get_type() == u_integer)
					ret = op<minus, double>(l, r);
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
		arraypair* tempmap = new arraypair;
		ret.set_value(tempmap);

		std::cerr << "no operator * exists for arrays" << std::endl;
	}
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
			ret = op<mul, int>(l, r);
		else if (l.get_type() == u_double)
			ret = op<mul, double>(l, r);
		else
		{
			// ret.value += l.value();
			// ret.value += r.value();
		}
	}
	else
	{
		if (l.get_type()==u_string)
		{
			// ret.value +=l.value();
			if (r.get_type() == u_integer)
			{
				// ret.value +=std::to_string(r.value());
			}
			else if (r.get_type() == u_double)
			{
				// ret.value +=std::to_string(r.value());
			}
		}
		else if (r.get_type()==u_string)
		{
			// ret.value +=l.value();
			if (l.get_type() == u_integer)
			{
				// ret.value +=std::to_string(l.value());
			}
			else if (l.get_type() == u_double)
			{
				// ret.value +=std::to_string(l.value());
			}
		}
		else if (l.get_type() == u_double || r.get_type() == u_double)
			if (l.get_type() == u_integer || r.get_type() == u_integer)
				ret = op<mul, double>(l, r);
	}
	return ret;
}

var_value operator/(var_value l, var_value r)
{
	var_value ret;
	if (l.get_type() == u_array || r.get_type() == u_array)
	{
		ret.set_type_noconvert(u_array);
		arraypair* tempmap = new arraypair;
		ret.set_value(tempmap);
		if (l.get_type() == u_array)
		{
			// TODO make this ordo m + n
			arraypair m1;
			if(!l.value(m1))
			{ std::cerr<<"conversion failed"<<std::endl; }

			if (r.get_type() == u_array)
			{
				arraypair m2;
				if(!r.value(m2))
				{ std::cerr<<"conversion failed"<<std::endl; }

				for(auto it = m2.begin(); it != m2.end(); ++it)
				{
					//TODO make it element / element? same with *
					std::vector<std::string> vec = l.find_elements_having_value(it->second);
					for(auto it2 = vec.begin(); it2 != vec.end(); ++it2)
						delete_from_arraypair(m1, *it2);
				}
			}
			else
			{
				std::vector<std::string> vec = l.find_elements_having_value(r);
				for(auto it2 = vec.begin(); it2 != vec.end(); ++it2)
					delete_from_arraypair(m1, *it2);
			}

			for(auto it = m1.begin(); it != m1.end(); ++it)
				ret.insert(it->first,it->second);
		}
		else
		{
			bool found = false;
			arraypair m2;
			r.value(m2);

			for(auto it = m2.begin();it!=m2.end();it++)
				if (it->second == l)
					found = true;

			if (!found)
				ret.insert(
					std::to_string(ret.get_size()),
					l
				);

		}
	}
	else
	{
		if (r.get_type() == u_integer)
		{
			int i;
			if (r.value(i) && i == 0)
				throw -1;

		}
		if (l.get_type() == r.get_type())
		{
			if (l.get_type() == u_integer)
				ret = op<division, int>(l, r);
			else if (l.get_type() == u_double)
				ret = op<division, double>(l, r);
			else
				s_div(l, r, ret);
		}
		else
		{
			if (l.get_type()==u_string || r.get_type() == u_string)
			{
				if (r.get_type() == u_integer ||
					r.get_type() == u_double  ||
					l.get_type() == u_integer ||
					l.get_type() == u_double
				) { s_div(l, r, ret); }
			}
			else
			{
				if (l.get_type() == u_integer)
					ret = op<division, double>(l, r);
				else if (r.get_type() == u_integer)
					ret = op<division, double>(l, r);
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
			ret = op<power, int>(l, r);
		else if (l.get_type() == u_double)
			ret = op<power, double>(l, r);
		else //u_string, u_array
		{
			//lehet hogy meg kéne próbálni konvertálni?
			std::cerr << "operator power only takes int or double" << std::endl;
		}
	}
	else
	{
		if (	!(
			l.get_type() == u_integer ||
			l.get_type() == u_double  ||
			r.get_type() == u_integer ||
			r.get_type() == u_double
		)) { std::cerr << "operator power only takes int or double" << std::endl; }
		else
			ret = op<power, double>(l, r);
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
			if (!l.value(i1))
			{ i1 = 0; std::cerr<<"conversion failed"<<std::endl; }

			if (!r.value(i2))
			{ i2 = 0; std::cerr<<"conversion failed"<<std::endl; }

			if(i2 == 0)
				throw 1;
			else
				ret = i1 % i2;
		}
		else
			throw 2;
	}
	else
		throw 2;

	return ret;
}

/*var_value operator++(var_value o)
{
	var_value ret;
	if (o.get_type() == u_integer)
	{
		ret = o.value() + 1;
	}
	else
	{
		throw 1;
	}
	return ret;
}*/

template <typename T>
std::enable_if_t<types::meta::is_one_of_v<T, int, double>, int>
compare(const var_value& lhs,const var_value& rhs)
{
	T var1, var2;
	if(!lhs.value(var1))
	{
		var1 = 0;
		std::cerr << "conversion failed" << std::endl;
	}

	if(!rhs.value(var2))
	{
		var2 = 0;
		std::cerr << "conversion failed" << std::endl;
	}

	if(var1 == var2)
		return 0;
	else if(var1 < var2)
		return -1;
	else
		return 1;
}

template <typename T>
std::enable_if_t<types::meta::is_one_of_v<T, std::string, arraypair>, int>
compare(var_value lhs, var_value rhs)
{
	T var1, var2;
	if(!lhs.value(var1))
		std::cerr << "conversion failed" << std::endl;

	if(!rhs.value(var2))
		std::cerr << "conversion failed" << std::endl;

	if(var1 == var2)
		return 0;
	else if(var1 < var2)
		return -1;
	else
		return 1;
}

int operator==(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
			return (compare<int>(l, r) == 0) ? 1 : 0;
		else if (l.get_type() == u_double)
			return (compare<double>(l, r) == 0) ? 1 : 0;

		else if (l.get_type() == u_string)
			return (compare<std::string>(l, r) == 0) ? 1 : 0;

		else if (l.get_type() == u_array)
			return (compare<arraypair>(l, r) == 0) ? 1 : 0;
	}
	else
	{
		if(l.get_type()==u_array || r.get_type() == u_array)
		{
			// TODO
			return 0;
		}
		else if (l.get_type() == u_string)
		{
			if (r.get_type() == u_integer || r.get_type() == u_double)
				return (compare<std::string>(l, r) == 0) ? 1 : 0;
		}
		else if (r.get_type() == u_string)
		{
			if (l.get_type() == u_integer || l.get_type() == u_double)
				return (compare<std::string>(l, r) == 0) ? 1 : 0;
		}
		else
		{
			if (l.get_type() == u_integer && r.get_type() == u_double)
				return (compare<double>(l, r) == 0) ? 1 : 0;

			else if (r.get_type() == u_integer && l.get_type() == u_double)
				return (compare<double>(l, r) == 0) ? 1 : 0;
		}
	}
	return -1; //just to get rid of the warning
}

int operator!=(var_value l, var_value r)
{ return !(l == r); }

int operator<(var_value l, var_value r)
{
	if (l.get_type() == r.get_type())
	{
		if (l.get_type() == u_integer)
			return (compare<int>(l, r) == -1) ? 1 : 0;
		else if (l.get_type() == u_double)
			return (compare<double>(l, r) == -1) ? 1 : 0;

		else if (l.get_type() == u_string)
			return (compare<std::string>(l, r) == -1) ? 1 : 0;

		else if (l.get_type() == u_array)
			return (compare<arraypair>(l, r) == -1) ? 1 : 0;
	}
	else
	{
		if(l.get_type()==u_array || r.get_type() == u_array)
		{
			//TODO
			return 0;
		}
		else if (l.get_type() == u_string)
		{
			if (r.get_type() == u_integer || r.get_type() == u_double)
				return (compare<std::string>(l, r) == -1) ? 1 : 0;
		}
		else if (r.get_type() == u_string)
		{
			if (l.get_type() == u_integer || l.get_type() == u_double)
				return (compare<std::string>(l, r) == -1) ? 1 : 0;
		}
		else
		{
			if (l.get_type() == u_integer && r.get_type() == u_double)
				return (compare<double>(l, r) == -1) ? 1 : 0;

			else if (r.get_type() == u_integer && l.get_type() == u_double)
				return (compare<double>(l, r) == -1) ? 1 : 0;
		}
	}
	return -1; //just to get rid of the warning
}

//vagy !== !<
int operator>(var_value l, var_value r)
{ return !(l < r || l == r); }

int operator>=(var_value l, var_value r)
{ return !(l < r); }

int operator<=(var_value l, var_value r)
{ return !(l > r); }

template <typename Ttype>
std::enable_if_t< types::meta::is_one_of_v<Ttype, int, double, std::string>, void >
out_stream(std::ostream& out, var_value &v)
{
	Ttype i;
		if (v.value(i))

	out << i;
}

std::ostream& operator<<(std::ostream& out, var_value &v)
{
	if (v.get_type() == u_integer)
		out_stream<int>(out, v);

	else if (v.get_type() == u_double)
		out_stream<double>(out, v);

	else if (v.get_type() == u_string)
		out_stream<std::string>(out, v);

	else if (v.get_type() == u_array)
	{
		arraypair a;
		if(v.value(a))
		{
			out << "[ ";
			auto it = a.begin();
			if (a.size() != 0)
			{
				out << it->second;
				it++;
				while(it!=a.end())
				{
					out << ", " << it->second;
					it++;
				}
			}
			out << " ]";
		}
		else
			std::cerr << "warning cannot cout arraypair" << std::endl;
	}
	return out;
}

/*std::istream& operator>>(std::istream& in, var_value &v)
{
	v.set_value(in);
	return in;
}*/


type var_value::get_type() const
{ return var_type; }

void var_value::set_type_noconvert(type t)
{ var_type = t; }

variable_desc::variable_desc()
{}

variable_desc::variable_desc(const variable_desc& other)
	: decl_row(other.decl_row)
	, value(other.value)
{}

variable_desc::variable_desc(int row_number, var_value v)
	: decl_row(row_number)
	, value(v)
{}

variable_desc& variable_desc::operator=(variable_desc right)
{
	decl_row = right.decl_row;
	value = right.value;
	return *this;
}

var_value variable_desc::return_value()
{ return value; }

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
		//ERROR
	}
	while(i>0)
	{
		i--;
		auto it = symbol_table[i].find(*name);
		if (it != symbol_table[i].end())
			return i;
	}
	return -1;
}

void Symbol_Table::set_value(std::string* name, variable_desc v)
{
	journal(journal::info, "symbol_table") << "set value of " << *name << journal::end;
	int i = find_variable(name);
	if (i != -1)
		symbol_table[i][*name] = v;

	else
		symbol_table[symbol_table.size() - 1][*name] = v;
}

void Symbol_Table::set_default_value(std::string name, var_value vv)
{
	journal(journal::info, "symbol_table") << "set value of " << name << journal::end;
	variable_desc v(-1, vv);
	symbol_table[0][name]= v;
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
	// itt 2x findol, optimalizalhato -
	// > Attila says: itt ugy lehetne, hogy visszaadod az iteratort is
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
		symbol_table.pop_back();
}