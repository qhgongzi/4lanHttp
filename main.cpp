#include <iostream>
#include "echttp/http.hpp"

using namespace echttp;

int sendNum=0;
int errNum=0;
int successNum=0;
http *chttp=new http();

void back(boost::shared_ptr<respone> ptr)
{
	std::cout<<std::string(ptr->body.begin(),ptr->body.end());
}

int main()
{	
	try{
			chttp->Get("http://www.xiaoqin.in",boost::bind(back,_1));
			//std::string msg(ret->body.begin(), ret->body.end());
			// std::cout<<msg;
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