#include "common.hpp"
#include "boost/asio.hpp"

namespace echttp
{

class chunk_reader
{
public:
	chunk_reader()
	  :m_chunk_end(false)
	{

	}

	~chunk_reader();

	void push(const std::vector<char> & buf)
	{
		for (std::vector<char>::iterator i = buf.begin(); i != buf.end(); ++i)
		{
			this->m_buf_queue.push(*i);
		}
	}

	std::vector<char> get()
	{
		if (m_chunk_rest==0)
		{
			while(!this->recved_size_delimter() && m_buf_queue.size()>0)
			{
				this->m_buf_delimter.push_back(m_buf_queue.pop());
			}

			if(this->recved_size_delimter())
			{
				m_chunk_rest=strtol(m_buf_delimter.c_str(),NULL,16)+2;//+2 because a chunk with a end of \r\n delimter;
				if(m_chunk_rest==0)
				{
					this->m_chunk_end==true;
					return std::vector<char>();
				}
				else
				{
					std::vector<char> v = this->pop(m_chunk_rest);
					m_chunk_rest-=v.size();
					if (m_chunk_rest==0)
					{
						return std::vector<char>(v.begin(), v.end()-2);//if is end of chunk ,remove the \r\n delimter;
					}else
					{
						return v;
					}
				}
			}
			else
			{
				return std::vector<char>();
			}

		}
		else
		{
			std::vector<char> v = this->pop(m_chunk_rest);
			m_chunk_rest-=v.size();
			return v;
		}
	}

	bool m_chunk_end;
private:

	std::vector<char> pop(size_t size)
	{
		std::vector<char> v;

		if (size>m_buf_queue.size())
		{
			size=m_buf_queue.size();
		}

		for (int i = 0; i < size; ++i)
		{
			v.push_back(m_buf_queue.pop());
		}

		return v;
	}

	bool recved_size_delimter()
	{
		return (m_buf_delimter.back()=='\n')
	}


	std::queue<char> m_buf_queue;
	size_t m_chunk_rest;
	std::vector<char> m_buf_delimter;
};

}