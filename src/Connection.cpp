#include "Connection.hpp"			
#include <unistd.h>
#include <stdio.h>
#include <string.h>

namespace con
{

	Connection::Connection(const char *addr,
			const char *port) : m_addr(addr), m_port(port) 
	{
		getAddrInfo();
	}

	Connection::~Connection()
	{
	}

	int Connection::getAddrInfo()
	{
		memset(&hints, 0, sizeof hints);

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;
		int rv; 

		if( (rv = getaddrinfo(NULL, m_port, &hints, &servinfo)) != 0)
		{
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			return 1;
		}
	}

	int Connection::bindPort()
	{
		for(p = servinfo; p != NULL; p -> ai_next)
		{
			matchFreeSocket();	

			if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			{
				fprintf(stderr, "setsocket \n");
				return 1;
			}

			if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
			{
				close(sockfd);
				fprintf(stderr, "server: bind \n");
				continue;
			}

			break;
		}

		freeaddrinfo(servinfo);

		if(p == NULL)
		{
			fprintf(stderr, "server: failed to bind \n");
			return 1;
		}
	}

	int Connection::listenPort()
	{
		if(listen(sockfd, BACKLOG) == 1)
		{
			fprintf(stderr, "listen \n");
			return 1;
		}
	}

	int Connection::acceptConnection()
	{
		sin_size = sizeof their_addr;
		newfd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if(newfd == -1)
		{
			fprintf(stderr, "accept \n");
			return 1;
		}
	}


	int Connection::Connect()
	{
		for(p = servinfo; p != NULL; p -> ai_next)
		{
			matchFreeSocket();

			if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
			{
				close(sockfd);
				fprintf(stderr, "connect\n");
			}	

			break;
		}
	}

	int Connection::readData(int socket)
	{
		int numbytes;
		if(recv(socket, readBuf, 1023, 0) == -1)
			fprintf(stderr, "read\n");

	}

	int Connection:: writeData(int socket)
	{
		if(send(socket, "Hello, wordl!", 13, 0) == -1)
			fprintf(stderr, "send\n");
	}

	int Connection::matchFreeSocket()
	{
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			fprintf(stderr, "server: socket \n");
		}
	}

}

