#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <netinet.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BACKLOG 5

namespace con
{
	class Connection
	{
		public:

			Connection(const char *addr = "localhost",
				const char *port = "1234");

			~Connection();

			int bindPort();

			int listenPort();

			int acceptConnection();

			int Connect();

			int getSocket();

			int getNewsocket();

			int readData(int socket);

			int writeData(int socket);

			int matchFreeSocket();

		private:
			int getAddrInfo();

			int sockfd;
			int newfd;
			int yes;

			struct addrinfo hints;
			struct addrinfo *servinfo, *p;

			struct sockaddr_storage their_addr;
			socklen_t sin_size;

			const char *m_addr;
			const char *m_port;
			char readBuf[1024];
			char writeBuf[1024];

	};
}
#endif
