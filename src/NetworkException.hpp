#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace con
{

	class NetworkException : public std::exception
	{
		public:

		explicit NetworkException(const char * message);

		virtual ~NetworkException() throw(); 

		virtual const char * what() const throw();

		private:

		std::string m_msg;

	};

}
#endif
