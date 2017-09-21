#include <iostream>
#include "Connection.hpp"

using namespace con;

int main(int argc, char *argv[])
{
	Connection con;
	con.Connect();

	Data data = con.readData();

	char ar[1024];
	data.getData(ar);
	std::cout << ar << '\n';
	return 0;
}
