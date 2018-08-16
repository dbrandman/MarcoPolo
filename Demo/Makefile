# Build MarcoPolo examples.

CC 			= gcc
BUILD_DIR 	= Build/

INCLUDES 	= -I../Source
SOURCES 	= ../Source/MarcoPolo.c ../Source/FindProcess.c
LIBRARIES 	= -lrt -lpthread -lzmq

.PHONY: all
all: MarcoPoloZMQ_Server MarcoPoloZMQ_Client

%:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $@.c $(SOURCES) $(INCLUDES) $(LIBRARIES)
	mv -f $@ $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)