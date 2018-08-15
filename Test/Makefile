
CC = gcc
INCLUDES = -I../\
			../MarcoPolo.c \
		 	../FindProcess.c

LIBRARIES = -lrt -lpthread

all: MarcoPolo FindProcess

MarcoPolo:
	$(CC) -o Test_MarcoPolo Test_MarcoPolo.c $(INCLUDES) $(LIBRARIES) 
FindProcess:
	$(CC) -o Test_FindProcess Test_FindProcess.c $(INCLUDES) $(LIBRARIES) 

clean:
	rm -f Test_FindProcess Test_MarcoPolo