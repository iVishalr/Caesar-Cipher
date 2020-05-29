CC=gcc
CFLAGS=-c -Wall
BUILD=build
SRC=src
all: 
	@if ! test -d $(BUILD); \
		then echo "\033[93msetting up build directory...\033[0m"; mkdir -p build;\
  	fi
	@if ! test -d bin; \
		then echo "\033[93msetting up bin directory...\033[0m"; mkdir -p bin; \
  	fi;
	@$(MAKE) start	
start: $(BUILD)/Caesar.o $(BUILD)/Server.o
	$(CC) $(BUILD)/Caesar.o $(BUILD)/Server.o
	@echo "\033[92mBuild Successful\033[0m"
$(BUILD)/Caesar.o: $(SRC)/Caesar.c
	$(CC) $(CFLAGS) -o $@ $<
$(BUILD)/Server.o: $(SRC)/Server.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	@rm -rf $(BUILD) a.out a.exe
	@echo "\033[92mDone\033[0m"
