#ifndef TYPES_TYPE_H
#define TYPES_TYPE_H

#include <string>
#include <typeinfo>

namespace types{
namespace type{

std::string demangle(const std::string &n);

template <class T>
std::string name(const T& t)
{ return demangle(typeid(t).name()); }

}}
#endif
