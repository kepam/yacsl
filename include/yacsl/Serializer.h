#pragma once

#include <yacsl/detail/MetaUtils.h>

namespace yacsl
{

template <class ClassT, class MappingT, class ProtocolWrapperT>
class Serializer
{
public:
	Serializer(MappingT& mapping, ProtocolWrapperT& protocol) : mapping_(mapping), protocol_(protocol) {}

	void serialize(const ClassT& object)
	{
		protocol_.startObject();
		meta::for_each(mapping_.getFields(), [&object, this](auto field)
				{
					const auto& value = object.*field.getPointer();
					protocol_.serialize(field.getName(), value, field.getMapping());
				}
		);
		protocol_.endObject();
	}
private:
	const MappingT& mapping_;
	ProtocolWrapperT& protocol_;
};

} // namespace yacsl
