#include <iostream>
#include "echttp/http.hpp"

using namespace echttp;

int sendNum=0;
int errNum=0;
int successNum=0;
http *chttp=new http();

int main()
{	
	try{
			boost::shared_ptr<echttp::respone> ret=chttp->Get("http://www.xiaoqin.in");
			std::string msg=ret->body.get();
			std::cout<<msg;
		}catch(boost::system::system_error &e)
		{
			boost::system::error_code ex=e.code();
			std::cout<<ex.message();
			std::cout<<ex.value();
		}
	
	
	int waitSingle;
	std::cin>>waitSingle;

	return 0;	
}