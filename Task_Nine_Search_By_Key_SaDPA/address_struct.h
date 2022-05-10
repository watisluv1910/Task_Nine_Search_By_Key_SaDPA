#ifndef ADDRESS_STRUCT_H
#define ADDRESS_STRUCT_H

#include <iostream>

struct address
{
	std::string street, city, state;
	int zip_code = 0;
};

#endif
