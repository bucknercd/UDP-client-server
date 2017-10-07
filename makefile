CFLAGS= -g -Wall

all: UDPClient UDPServer

UPDClient: UDPClient.o
UDPClient.o: UDPClient.c

UDPServer: UDPServer.o
UDPServer.o: UDPServer.c

server:
	./UDPServer

client:
	./UDPClient

clean:
	rm *.o UDPServer UDPClient
