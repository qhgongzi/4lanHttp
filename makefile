http.exe : main.o http.o httpclient.o ciopool.o webrequest.o webrespone.o weblib.o
	g++ -o http.exe  main.o http.o httpclient.o ciopool.o webrequest.o webrespone.o weblib.o \
	-L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -lpthread -lboost_thread -lboost_regex
	#g++ main.cpp  -L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -o http.exe

main.o:main.cpp
	g++ -c main.cpp -I/usr/local/ssl/include -o main.o

http.o:
	g++ -c -I/usr/local/ssl/include http/Http.cpp -o http.o

httpclient.o:
	g++ -c -I/usr/local/ssl/include http/HttpClient.cpp -o httpclient.o

ciopool.o:
	g++ -c http/CIoPool.cpp -o ciopool.o

webrequest.o:
	g++ -c -I/usr/local/ssl/include http/WebRequest.cpp -o webrequest.o

webrespone.o:
	g++ -c -I/usr/local/ssl/include http/WebRespone.cpp -o webrespone.o

weblib.o:
	g++ -c -I/usr/local/ssl/include http/weblib.cpp 

clean:
	rm -rf *.o

