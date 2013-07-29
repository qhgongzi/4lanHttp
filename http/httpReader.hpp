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