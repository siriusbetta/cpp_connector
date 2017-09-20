#ifndef DATA_HPP
#define DATA_HPP

#define DATA_SIZE	1024

namespace con
{

	class Data
	{
	public:

		Data();

		~Data();

		void putData(char *data, size_t length);

		size_t getData(char *dest);

		void clearBuffer();

	private:

		char buffer[DATA_SIZE];

		size_t data_length;

	};

}
#endif
