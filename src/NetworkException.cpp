#include "NetworkException.hpp"

namespace con
{
	NetworkException::NetworkException(const char * message) : 
			m_msg( message )
	{
	}

	NetworkException::~NetworkException() throw()
	{

	}

	const char * NetworkException::what() const throw()
	{
		return m_msg.c_str();
	}

}
