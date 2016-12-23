#include <iostream>

#include <yacsl/ObjectMapping.h>

struct Sample
{
	int x;
	int y;
	double value;
};

int main(int argc, char** argv)
{
	auto mapping = yacsl::MappingBuilder<Sample>()
		.addField("x", &Sample::x)
		.addField("y", &Sample::y)
		.addField("value", &Sample::value)
		.getMapping();
}
