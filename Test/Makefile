# Build MarcoPolo tests.

CC 			= gcc
BUILD_DIR 	= Build/

INCLUDES 	= -I../Source
SOURCES 	= ../Source/MarcoPolo.c ../Source/FindProcess.c
LIBRARIES 	= -lrt -lpthread

all: Test_MarcoPolo Test_FindProcess

Test_MarcoPolo:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $@.c $(SOURCES) $(INCLUDES) $(LIBRARIES)
	mv -f $@ $(BUILD_DIR)

Test_FindProcess:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $@.c $(SOURCES) $(INCLUDES) $(LIBRARIES)
	mv -f $@ $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)