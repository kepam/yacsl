#pragma once

#include <tuple>

#include <yacsl/detail/Field.h>
#include <yacsl/detail/MetaUtils.h>

namespace yacsl
{

/* Defines mapping of fields for object serialization/deserialization.
 *
 * Template class enables iteration over defined fields. 
 */
template <class ClassT, class... FieldsTs>
class ObjectMapping 
{
public:
	ObjectMapping(std::tuple<Field<ClassT, FieldsTs>...> t) : f_(t) {}

	template<class T>
	void setField(ClassT& obj, const std::string& name, T& value) {
		meta::for_each(f_, [&obj, &name, &value](auto field) { if (field.name_ == name) { meta::assign(obj, field.ptr_, value); }});
	}

	template<class T>
	void pushBack(ClassT& obj, const std::string& name, T& value) {
		meta::for_each(f_, [&obj, &name, &value](auto field) { if (field.name_ == name) { meta::push_back(obj, field.ptr_, value); }});
	}

private:
	std::tuple<Field<ClassT, FieldsTs>...> f_;
};

/* Convenient builder for ObjectMapping's. */ 
template <class ClassT, class... FieldsTs>
class MappingBuilder
{
public:
	MappingBuilder() {}

	MappingBuilder(std::tuple<Field<ClassT, FieldsTs>...> tuple) : tuple_(tuple) {}

	template <class FieldT>
	MappingBuilder<ClassT, FieldsTs..., FieldT> addField(const std::string& name, FieldT (ClassT::*field))
	{
		return MappingBuilder<ClassT, FieldsTs..., FieldT>(std::tuple_cat(tuple_, std::make_tuple(Field<ClassT, FieldT>(name, field))));
	}

	ObjectMapping<ClassT, FieldsTs...> getMapping()
	{
		return ObjectMapping<ClassT, FieldsTs...>(tuple_);
	}
private:
	std::tuple<Field<ClassT, FieldsTs>...> tuple_;
};

} // namespace yacsl
