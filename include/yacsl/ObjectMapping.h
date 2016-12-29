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
	ObjectMapping(std::tuple<FieldsTs...> fields) : fields_(fields) {}

	template<class T>
	void setField(ClassT& obj, const std::string& name, T& value) 
	{
		meta::for_each(fields_, [&obj, &name, &value](auto field) { if (field.name_ == name) { meta::assign(obj, field.ptr_, value); }});
	}

	template<class T>
	void pushBack(ClassT& obj, const std::string& name, T& value)
	{
		meta::for_each(fields_, [&obj, &name, &value](auto field) { if (field.name_ == name) { meta::push_back(obj, field.ptr_, value); }});
	}

	const std::tuple<FieldsTs...> getFields() const
	{
		return fields_;
	}

private:
	std::tuple<FieldsTs...> fields_;
};

/* Convenient builder for ObjectMapping's. */ 
template <class ClassT, class... FieldsTs>
class MappingBuilder
{
public:
	MappingBuilder() {}

	MappingBuilder(std::tuple<FieldsTs...> tuple) : tuple_(tuple) {}

	template <class FieldT>
	MappingBuilder<ClassT, FieldsTs..., Field<ClassT, FieldT, FieldT>> addField(const std::string& name, FieldT (ClassT::*field))
	{
		return MappingBuilder<ClassT, FieldsTs..., Field<ClassT, FieldT, FieldT>>
			(std::tuple_cat(tuple_, std::make_tuple(Field<ClassT, FieldT>(name, field))));
	}

	template <class FieldT, class MappingT>
	MappingBuilder<ClassT, FieldsTs..., Field<ClassT, FieldT, MappingT>> addField(const std::string& name, FieldT (ClassT::*field), const MappingT& mapping)
	{
		return MappingBuilder<ClassT, FieldsTs..., Field<ClassT, FieldT, MappingT>>(
				std::tuple_cat(tuple_, std::make_tuple(Field<ClassT, FieldT, MappingT>(name, field, mapping))));
	}
	

	ObjectMapping<ClassT, FieldsTs...> getMapping()
	{
		return ObjectMapping<ClassT, FieldsTs...>(tuple_);
	}
private:
	std::tuple<FieldsTs...> tuple_;
};

} // namespace yacsl
