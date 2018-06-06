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

CC 		= gcc
CFLAGS 		= -Wall -Werror -fpic
LDFLAGS 	= -shared
RM 		= rm -f
TARGET_LIB 	= libmarcopolo.so

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
	$(RM) $(OBJS)

.PHONY: clean
clean:
	-$(RM) $(TARGET_LIB) $(OBJS)