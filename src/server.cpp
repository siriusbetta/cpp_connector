#include <iostream>
#include "Connection.hpp"
#include "Data.hpp"
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

using namespace con;

std::vector<std::thread> threads;
std::mutex thm;

class ConnectionThread
{

public:
	ConnectionThread(Connection n_con, int n_id) : conn(n_con), id(n_id)
	{

	}

	~ConnectionThread()
	{

	}

	void operator () ()
	{
		char buf[512];

		while(conn.readData(buf, 512) > 0)
		{
			std::cout << "Received: " << buf << " by " << id << std::endl;

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		std::cout << "Close connection " << id << std::endl;
	}


private:

	Connection conn;

	int id;
};


void joinThreads()
{

	std::vector<std::thread>::iterator it;
	while( true )
	{

		for(it = threads.begin(); it != threads.end(); ++it)
		{
			if(it -> joinable() && it != threads.end())
			{
				it->join();
				
				std::cout << "Thread join: size of: " << threads.size() << std::endl;
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

int main(int argc, char *argv[])
{
	Connection con;

	int thrCnt = 0;


	con.bindPort();
	con.listenPort();
	std::thread monitor(joinThreads);

	while(true)
	{
		Connection new_con = con.acceptConnection();

		thrCnt++;

		ConnectionThread conThr(new_con, thrCnt);

		std::cout << "Accepted: " << thrCnt << std::endl;

		std::thread t( (conThr) );
		threads.push_back( move(t) );
	}
	
	
	return 0;
}
