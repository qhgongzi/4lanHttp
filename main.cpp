#include <iostream>
#include "http/Http.h"

int sendNum=0;
int errNum=0;
int successNum=0;
echttp *http=new echttp();

int main()
{
	while(true)
	{
		boost::shared_ptr<respone> ret=http->Get("http://www.xiaoqin.in");
		std::string msg=ret->msg.get();
		std::cout<<msg;
		sleep(1);
	}
	

	int waitSingle;
	std::cin>>waitSingle;

	return 0;	
}