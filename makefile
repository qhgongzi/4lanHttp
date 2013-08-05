http.exe : main.o 
	g++ -g -o http.exe  main.o \
	-L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -lpthread -lboost_thread -lboost_regex
	#g++ main.cpp  -L/usr/local/ssl/lib -lssl -lcrypto -lboost_system -ldl -o http.exe

main.o:main.cpp
	g++ -g -c main.cpp -I/usr/local/ssl/include -o main.o

