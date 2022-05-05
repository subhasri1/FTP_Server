all: ftps ftpc
ftps: ftpserver.cpp func.o
	g++ -o ftps ftpserver.cpp func.o
ftpc: ftpclient.cpp func.o
	g++ -o ftpc ftpclient.cpp func.o
func.o: func.cpp include/userauth.h
	g++ -c func.cpp
