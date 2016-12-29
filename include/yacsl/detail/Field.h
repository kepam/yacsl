#pragma once

#include <type_traits>

namespace yacsl
{

template <class ClassT, class FieldT, class MappingT = FieldT>
class Field 
{
public:
	typedef FieldT (ClassT::*PoinerT);
	Field(const std::string& name, FieldT (ClassT::*ptr)) : name_(name), ptr_(ptr) {}
	Field(const std::string& name, FieldT (ClassT::*ptr), const MappingT& mapping) : name_(name), ptr_(ptr), mapping_(mapping) {}

	const std::string& getName() const
	{
		return name_;
	}
	PoinerT getPointer() const
	{
		return ptr_;
	}
private:
	std::string name_;
	FieldT (ClassT::*ptr_);
	typename std::conditional< std::is_same<MappingT, FieldT>::value,
			 std::nullptr_t, 
			 std::add_lvalue_reference_t<typename std::add_const_t<MappingT>>>::type mapping_;
};

} // namespace yacsl
