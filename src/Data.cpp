#include <memory.h>
#include <stdio.h>

#include "Data.hpp"

namespace con
{
	Data::Data()
	{

	}

	Data::~Data()
	{

	}

	void Data::putData(char *data, size_t length)
	{
		memcpy(buffer, data, length);
		data_length = length;
	}

	size_t Data::getData(char *dest)
	{
		memcpy(dest, buffer, data_length);
		return data_length;
	}

	void Data::clearBuffer()
	{
		memset(buffer, 0, DATA_SIZE);
	}

}
