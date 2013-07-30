#include "common.h"
#include "boost/asio.hpp"

template <class Tsock>
class httpReader
{
	

	public:
		bool bChunked;
		std::string header;

		void httpReader(Tsock sock)
	 	{
			this->m_scok=sock;
			this->read();

		}

		void read()
		{
			int headSize;
			
			headSize=boost::asio::read_until(m_sock,respone_,"\r\n\r\n");
			
			nHeaderLen=headSize;
			std::istream response_stream(&respone_);
			response_stream.unsetf(std::ios_base::skipws);//asio::streambuf 转换成istream 并且忽略空格

			//将数据流追加到header里
			int readSize=respone_.size();

			char * head=new char[headSize+1];
			memset(head,0,headSize+1);
			response_stream.read(head,headSize);
			m_respone->header=head;
			delete head;

			int rdContentSize=readSize-m_respone->header.size();

			char * cont=NULL;
			//获取httpContent的长度
			if(m_respone->header.find("Content-Length")!=std::string::npos)
			{
				std::string len=m_respone->header.substr(m_respone->header.find("Content-Length: ")+16);
				len=len.substr(0,len.find_first_of("\r"));
				nContentLen=atoi(len.c_str());

				if(protocol_==1){
					boost::asio::read(ssl_sock,respone_,boost::asio::transfer_at_least(nContentLen-rdContentSize));
				}else{
					boost::asio::read(socket_,respone_,boost::asio::transfer_at_least(nContentLen-rdContentSize));
				}

				nContentLen=respone_.size();
				cont=new char[nContentLen+1]; //此处申请了内存，注意释放。
				memset(cont+nContentLen,0,1);
				response_stream.read(cont,nContentLen);

			}
			else if(m_respone->header.find("Transfer-Encoding: chunked")!=std::string::npos)
			{
				while (true)
				{
					int contSize=0;
					if(protocol_==1){
						contSize=boost::asio::read_until(ssl_sock,respone_,"\r\n");
					}else{
						contSize=boost::asio::read_until(socket_,respone_,"\r\n");
					}

					int readLen=respone_.size()-contSize;

					char *chunkStr=new char[contSize]; //此处申请了内存，注意释放。
					response_stream.read(chunkStr,contSize);
					memset(chunkStr+contSize-2,0,2);
					long nextReadSize=strtol(chunkStr,NULL,16);
					if(nextReadSize==0) break;
					delete chunkStr;

					char * htmlBuf=new char[nextReadSize+2];

					if(nextReadSize>readLen){
						if(protocol_==1){
							boost::asio::read(ssl_sock,respone_,boost::asio::transfer_at_least(nextReadSize-readLen+2));
						}else{
							boost::asio::read(socket_,respone_,boost::asio::transfer_at_least(nextReadSize-readLen+2));
						}
					}

					response_stream.read(htmlBuf,nextReadSize+2);

					if(cont==NULL){
						cont=htmlBuf;
						memset(htmlBuf+nextReadSize,0,2);
						nContentLen=nextReadSize;
					}else{
						char * newCont=new char[nContentLen+nextReadSize+1];
						memset(newCont+nContentLen+nextReadSize,0,1);
						memcpy(newCont,cont,nContentLen);
						memcpy(newCont+nContentLen,htmlBuf,nextReadSize);
						delete  cont;
						delete  htmlBuf;

						cont=newCont;
						nContentLen+=nextReadSize;
					}
				}

			}

			boost::shared_array<char> content(cont);
	

			if(header.find("chunked")!=header.npos)
			{
				this->bChunked=true;
			}else{
				this->bChunked=false;
			}
		}



	private:
		Tsock m_sock;

}