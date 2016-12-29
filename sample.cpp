#include <iostream>

#include <yacsl/ObjectMapping.h>

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
}
