http.exe : main.o http.o httpclient.o ciopool.o webrequest.o webrespone.o weblib.o
	g++ -g -o http.exe  main.o http.o httpclient.o ciopool.o webrequest.o webrespone.o weblib.o \
	-L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -lpthread -lboost_thread -lboost_regex
	#g++ main.cpp  -L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -o http.exe

main.o:main.cpp
	g++ -g -c main.cpp -I/usr/local/ssl/include -o main.o

http.o:
	g++ -g -c -I/usr/local/ssl/include http/Http.cpp -o http.o

httpclient.o:http/HttpClient.cpp http/httpReader.hpp
	g++ -g -c -I/usr/local/ssl/include http/HttpClient.cpp -o httpclient.o

ciopool.o:
	g++ -g -c http/CIoPool.cpp -o ciopool.o

webrequest.o:
	g++ -g -c -I/usr/local/ssl/include http/WebRequest.cpp -o webrequest.o

webrespone.o:
	g++ -g -c -I/usr/local/ssl/include http/WebRespone.cpp -o webrespone.o

weblib.o:
	g++ -g -c -I/usr/local/ssl/include http/weblib.cpp 

clean:
	rm -rf *.o

