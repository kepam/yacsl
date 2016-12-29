#pragma once

#include <string>

#include <rapidjson/prettywriter.h>

namespace yacsl
{
namespace protocol
{

template<class RapidJSONWriter>
class JSON
{
public:
	JSON(RapidJSONWriter& writer) : writer_(writer) {}

	void startObject()
	{
		writer_.StartObject();
	}

	void endObject()
	{
		writer_.EndObject();
	}

	template<class T>
	void serialize(const std::string& name, const T& value)
	{
		writer_.Key(name.c_str());	
		serialize(value);
	}

	void serialize(int32_t value)
	{
		writer_.Int(value);
	}

	void serialize(int64_t value) 
	{
		writer_.Int64(value);
	}

	void serialize(uint32_t value) 
	{
		writer_.Uint(value);
	}

	void serialize(uint64_t value) 
	{
		writer_.Uint64(value);
	}

	void serialize(const std::string& value) 
	{
		writer_.String(value.c_str());
	}

	void serialize(double value) {
		writer_.Double(value);
	}

private:
	RapidJSONWriter& writer_;
};

} // namespace protocol
} // namespace yacsl
