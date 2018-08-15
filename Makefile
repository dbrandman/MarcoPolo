# To compile MarcoPolo without FindProcess:
#
# 	$ make
#
# To compile MarcoPolo *with* FindProcess:
#
# 	$ make include=FindProcess
#
# To clean:
# 
# 	$ make clean

CC 			= gcc
CFLAGS 		= -Wall -Werror -fpic
LDFLAGS 	= -shared
TARGET_LIB 	= libmarcopolo.so
BUILD_DIR 	= Build/

ifeq ($(include), FindProcess)
	SRCS = MarcoPolo.c FindProcess.c
	OBJS = MarcoPolo.o FindProcess.o
else
	SRCS = MarcoPolo.c
	OBJS = MarcoPolo.o
endif

.PHONY: all
all: MarcoPolo

MarcoPolo: 
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) $(OBJS)
	rm -f $(OBJS)
	mkdir -p $(BUILD_DIR)
	mv -f $(TARGET_LIB) $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJS) $(BUILD_DIR)