#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "Connection.hpp"
#include "NetworkException.hpp"

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

	Connection::Connection(const Connection & c)
	{
		this->m_addr = c.m_addr;
		this->m_port = c.m_addr;
	}

	Connection & Connection::operator = (const Connection & c)
	{
		this->m_addr = c.m_addr;
		this->m_port = c.m_addr;
		return *this;
	}

	void Connection::getAddrInfo()
	{
		memset(&hints, 0, sizeof hints);

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;
		int rv;

		if( (rv = getaddrinfo(NULL, m_port, &hints, &servinfo)) != 0)
		{
			//fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			throw new NetworkException("getaddrinfo exception");
		}
	}

	void Connection::bindPort()
	{
		for(p = servinfo; p != NULL; p -> ai_next)
		{
			matchFreeSocket();

			if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			{
				//fprintf(stderr, "setsocket \n");

				throw new NetworkException("setsockopt exception");
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
			throw new NetworkException("server: failed to bind exception");
		}
	}

	void Connection::listenPort()
	{
		if(listen(sockfd, BACKLOG) == 1)
		{
			fprintf(stderr, "listen \n");
			throw new NetworkException("listen exception");
		}
	}

	Connection Connection::acceptConnection()
	{
		char ipstr[INET6_ADDRSTRLEN];

		sin_size = sizeof their_addr;
		newfd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if(newfd == -1)
		{
			fprintf(stderr, "accept \n");
			throw new NetworkException("accept exception");
		}
		Connection c;
		c.sockfd = newfd;
		c.m_addr = m_addr;
		c.m_port = m_port;

		return c;
	}

	int Connection::getSocket()
	{
		return sockfd;
	}

	int Connection::getNewSocket()
	{
		return newfd;
	}

	void Connection::Connect()
	{
		for(p = servinfo; p != NULL; p -> ai_next)
		{
			matchFreeSocket();

			if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
			{
				close(sockfd);
				fprintf(stderr, "connect\n");
				throw new NetworkException("connect exception");
			}

			break;
		}
	}

	int Connection::readData(char *buffer, size_t buffer_length)
	{
		int numbytes;
		if( (numbytes = recv(sockfd, buffer, DATA_SIZE - 1, 0)) == -1)
		{
			fprintf(stderr, "read\n");
			throw NetworkException("read: exception");
		}
		return numbytes;
	}

	Data Connection::readData()
	{
		Data data;
		char readBuf[DATA_SIZE];

		int numbytes = readData(readBuf, DATA_SIZE);

		data.putData(readBuf, numbytes);
		return data;
	}

	int Connection::writeData(char *buffer, size_t buffer_length)
	{
		if(send(sockfd, buffer, buffer_length, 0) == -1)
		{
			fprintf(stderr, "send\n");
			throw NetworkException("write: exception");
		}
	}

	int Connection:: writeData(Data data)
	{
		char buf[DATA_SIZE];

		int dataLength = data.getData(buf);

		return writeData(buf, dataLength);
	}

	int Connection::closeConnection()
	{
		close(sockfd);
	}

	int Connection::matchFreeSocket()
	{
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			fprintf(stderr, "server: socket \n");
			throw new NetworkException("socket exception");
		}
	}

	void *Connection::getInAddr(struct sockaddr *sa)
	{

		if(sa -> sa_family == AF_INET)
		{
			return &( ( ( struct sockaddr_in* )sa)->sin_addr);
		}

		return &( ( ( struct sockaddr_in6* )sa)->sin6_addr);
	}

	short Connection::getInPort(struct sockaddr *sa)
	{

		if(sa -> sa_family == AF_INET)
		{
			return ( ( ( struct sockaddr_in* )sa)->sin_port);
		}

		return ( ( ( struct sockaddr_in6* )sa)->sin6_port);
	}

}
