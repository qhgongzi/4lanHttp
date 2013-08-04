#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace echttp
{
	class iopool
	{
	    public:
	    	boost::asio::io_service io;

	        static iopool* Instance(int threadNum)
	        {
	        	if (NULL==iopool::pool)
				{
				    iopool::pool=new iopool(threadNum);
				}
				return iopool::pool;

	        }

	        void Stop(void)
	        {
	        	io.stop();
	        }

	        

	    private:
	        boost::asio::io_service::work work;
	        boost::thread_group workers;


	        iopool(int threadNum):work(io)
			{
				for(int i=0;i<threadNum;++i)
				{
					workers.create_thread(boost::bind(&boost::asio::io_service::run,&io));
				}
			}

	        ~iopool(void)
	        {
	        	io.stop();
	        }

	    protected:
	        static iopool * pool;
	};
}

