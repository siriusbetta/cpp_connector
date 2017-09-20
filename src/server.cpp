#include <iostream>
#include "Connection.hpp"
#include "Data.hpp"

using namespace con;

int main(int argc, char *argv[])
{
	Connection con;

	con.bindPort();
	con.listenPort();
	
	Connection new_con = con.acceptConnection();

	char *text = "Helllo";
	Data data;
	data.putData(text, 6);
	new_con.writeData(data);
	return 0;
}
