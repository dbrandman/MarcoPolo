
CC = gcc
INCLUDES = -I../\
			../MarcoPolo.c \
		 	../FindProcess.c

LIBRARIES = -lrt -lpthread
BUILD_DIR = Build/

all: Test_MarcoPolo Test_FindProcess

Test_MarcoPolo:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $@.c $(INCLUDES) $(LIBRARIES)
	mv -f $@ $(BUILD_DIR)
Test_FindProcess:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $@.c $(INCLUDES) $(LIBRARIES)
	mv -f $@ $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)