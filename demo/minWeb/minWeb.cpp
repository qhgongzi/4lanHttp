// minWeb.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Http.h"

int sendNum=0;
int errNum=0;
int successNum=0;
CHttp *http=new CHttp();

void back(std::map<std::string,std::string> respone, char * msg , int nLen)
{
	sendNum++;
	if(respone["responeCode"]=="200"){
		successNum++;
	}else{
		errNum++;
	}
	std::cout<<"���ʹ�����"<<sendNum<<"�ɹ�������"<<successNum<<"err:"<<errNum<<"\r\n";
	http->AsyGet("http://www.xiaoqin.in/",boost::bind(back,_1,_2,_3));
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	http->AsyGet("http://www.xiaoqin.in/",boost::bind(back,_1,_2,_3));

	int waitSingle;
	std::cin>>waitSingle;
	return 0;
}

