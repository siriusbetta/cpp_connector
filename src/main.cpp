#include <iostream>
#include "Connection.hpp"

using namespace con;

int main(int argc, char *argv[])
{
	Connection con;

	con.bindPort();
	con.listenPort();
	con.acceptConnection();


	return 0;
}
