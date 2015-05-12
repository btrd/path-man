CC=gcc
CFLAGS=-Wall -g -std=c99
#----------------------------------------------
all : Server Client 
#----------------------------------------------
Server : Server.o xdr_population.o
	gcc -o Server Server.o xdr_population.o
#----------------------------------------------
Client : Client.o xdr_population.o
	gcc -o Client Client.o xdr_population.o
#----------------------------------------------
%.o : %.c
	gcc -o $@ $(CFLAGS) -c $^

clean :
	/bin/rm -f *.o Server Client *~ core* pok* *.ps
