#include <iostream>
#include "Connection.hpp"

using namespace con;

int main(int argc, char *argv[])
{
	Connection con;
	con.Connect();

	char *text = "Helllo";
	int inp = 0;
	while(inp != 2)
	{
		std::cout << "Input some: " << std::endl;
		con.writeData(text, 6);
		std::cin >> inp;
		std::cout << "Inputed : " << inp << std::endl;
	}
	con.closeConnection();

	return 0;
}
