#pragma once

namespace yacsl
{

template <class ClassT, class FieldT>
class Field {
public:
	Field(const std::string& name, FieldT (ClassT::*ptr)) : name_(name), ptr_(ptr) {}
private:
	std::string name_;
	FieldT (ClassT::*ptr_);
};

} // namespace yacsl
