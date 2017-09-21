#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BACKLOG 5
#define DATA_SIZE	1024

#include "Data.hpp"

namespace con
{

	class Connection
	{
		public:

			Connection(const char *addr = "localhost",
				const char *port = "3940");

			Connection(const Connection & c);

			~Connection();

			Connection & operator = (const Connection & c);

			void bindPort();

			void listenPort();

			Connection acceptConnection();

			void Connect();

			int getSocket();

			int getNewSocket();

			Data readData();

			int readData(char *buffer, size_t buffer_length);

			int writeData(Data data);

			itn writeData(char *buffer, size_t buffer_length);

			int closeConnection();

			int matchFreeSocket();

			const char *m_addr;

			const char *m_port;

		private:

			void getAddrInfo();

			void *getInAddr(struct sockaddr *sa);

			short getInPort(struct sockaddr *sa);

			int sockfd;
			int newfd;
			int yes;

			struct addrinfo hints;

			struct addrinfo *servinfo, *p;

			struct sockaddr_storage their_addr;

			socklen_t sin_size;

			char writeBuf[1024];

	};

}
#endif
