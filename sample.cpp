#include <iostream>

#include <yacsl/ObjectMapping.h>
#include <yacsl/Serializer.h>
#include <yacsl/protocol/JSON.h>

struct SampleClass
{
	int x;
	int y;
	double value;
};

struct AnotherClass
{
	SampleClass s;
	std::string data;
};

int main(int argc, char** argv)
{
	auto sampleMapping = yacsl::MappingBuilder<SampleClass>()
		.addField("x", &SampleClass::x)
		.addField("y", &SampleClass::y)
		.addField("value", &SampleClass::value)
		.getMapping();

	auto anotherMapping = yacsl::MappingBuilder<AnotherClass>()
		.addField("s", &AnotherClass::s, sampleMapping)
		.addField("data", &AnotherClass::data)
		.getMapping();


	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);

	yacsl::protocol::JSON<decltype(writer)> protocol(writer);
	auto serializer = yacsl::Serializer<AnotherClass, decltype(anotherMapping), decltype(protocol)>(anotherMapping, protocol);

	AnotherClass data;
	data.s.x = 1;
	data.s.y = 2;
	data.s.value = 3;
	data.data = "four";

	serializer.serialize(data);

	std::cout << s.GetString() << std::endl;
}
