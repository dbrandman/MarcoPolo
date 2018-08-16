# MarcoPolo makefile.
#
# Please see the README for more info on the build process.

CC 		= gcc
RM 		= rm -f
CFLAGS 		= -Wall -Werror -fpic
LDFLAGS 	= -shared
TARGET_LIB 	= libmarcopolo.so

SOURCE_DIR 	= Source
BUILD_DIR 	= Build
TEST_DIR 	= Test
DEMO_DIR 	= Demo

INSTALL_LIB 	= /usr/local/lib
INSTALL_INC 	= /usr/local/include

SOURCES		= $(SOURCE_DIR)/MarcoPolo.c $(SOURCE_DIR)/FindProcess.c
OBJECTS		= MarcoPolo.o FindProcess.o

.PHONY: build
build: MarcoPolo

MarcoPolo: 
	$(CC) -c $(CFLAGS) $(SOURCES)
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) $(OBJECTS)
	$(RM) $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	mv -f $(TARGET_LIB) $(BUILD_DIR)

test:
	make -C Test/

demo:
	make -C Demo/

install:
	@if ! [ -e Build/libmarcopolo.so ]; then 					\
		echo "Please build the library first with \`make build\`."; 		\
	else 										\
		sudo cp -v -f Build/libmarcopolo.so $(INSTALL_LIB)/libmarcopolo.so; 	\
		sudo cp -v -f 								\
			$(SOURCE_DIR)/MarcoPolo.h /usr/local/include/MarcoPolo.h; 	\
		sudo cp -v -f 								\
			$(SOURCE_DIR)/FindProcess.h /usr/local/include/FindProcess.h;	\
		sudo ldconfig -n $(INSTALL_LIB); 					\
	fi

uninstall:
	sudo $(RM) $(INSTALL_LIB)/libmarcopolo.so
	sudo $(RM) $(INSTALL_INC)/MarcoPolo.h
	sudo $(RM) $(INSTALL_INC)/FindProcess.h
	sudo ldconfig -n $(INSTALL_LIB)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(BUILD_DIR)
	make -C $(TEST_DIR) clean
	make -C $(DEMO_DIR) clean

all: build test demo