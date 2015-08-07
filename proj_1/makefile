gcc := "/usr/bin/gcc"
all: server client 
server: server.c msg.h
	echo $^
	$(gcc) -o server -lcrypto -lssl -Wno-error=deprecated-declarations $<
client: client.c msg.h
	echo $^
	$(gcc) -o client -lcrypto -lssl -Wno-error=deprecated-declarations $<
	
