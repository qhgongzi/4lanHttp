#include <iostream>
#include "http/echttp.hpp"

using namespace echttp;

int sendNum=0;
int errNum=0;
int successNum=0;
echttp *http=new echttp();

int main()
{
	while(true)
	{
		boost::shared_ptr<echttp::respone> ret=http->Get("http://www.xiaoqin.in");
		std::string msg=ret->body.get();
		std::cout<<msg;
		sleep(1);
	}
	

	int waitSingle;
	std::cin>>waitSingle;

	return 0;	
}