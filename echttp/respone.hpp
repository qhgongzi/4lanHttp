#ifndef __RESPONE_HPP__
#define __RESPONE_HPP__


#include "common.hpp"
#include <map>

namespace  echttp{

	struct respone
	{

		int errorCode;
		std::string errMsg;

		boost::shared_array<char> body;
		size_t len;
		std::string header;
		
		int statusCode;
		std::map<std::string,std::string> headerMap;

	};

	
}

#endif