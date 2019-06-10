#  / ____| |  \/  |   /\   | |/ /  ____|  ____|_   _| |    |  ____|
# | |      | \  / |  /  \  | ' /| |__  | |__    | | | |    | |__   
# | |      | |\/| | / /\ \ |  < |  __| |  __|   | | | |    |  __|  
# | |____  | |  | |/ ____ \| . \| |____| |     _| |_| |____| |____ 
#  \_____| |_|  |_/_/    \_\_|\_\______|_|    |_____|______|______|
#                                                                  
#                                                                  

SHELL       = /bin/sh
detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
BIN_NAME    = out
CC          = g++-8
LD          = g++-8
CFLAGS      = -Wall -Wextra -Wno-unused-parameter -pedantic -fopenmp

ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
else
	CFLAGS += -O3
endif

# ____  ____  _     _____  ____  ____  _    _    
#/   _\/  _ \/ \  //__ __\/  __\/  _ \/ \  / \   
#|  /  | / \|| |\ || / \  |  \/|| / \|| |  | |   
#|  \__| \_/|| | \|| | |  |    /| \_/|| |_/\ |_/\
#\____/\____/\_/  \| \_/  \_/\_\\____/\____|____/
                                                

SRC_DIR    = src
INCLUDES   = -I include
BIN_DIR    = bin
BUILD_DIR  = build
SRC        = $(wildcard $(SRC_DIR)/*.cpp)
OBJ        = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEPS       = $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,$(OBJ))
DOC_DIR    = docs
PROGRAM    = program

vpath %.cpp $(SRC_DIR)

# ____  _     _    _________ 
#/  __\/ \ /\/ \  /  __/ ___\
#|  \/|| | ||| |  |  \ |    \
#|    /| \_/|| |_/\  /_\___ |
#\_/\_\\____/\____|____\____/

.DEFAULT_GOAL = all

.PHONY: run fmt doc checkdirs all clean

$(BUILD_DIR)/%.d: %.cpp
	$(CC) -M $(CFLAGS) $(INCLUDES) $< -o $@ 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ 

$(BIN_DIR)/$(BIN_NAME): $(DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) 

run:
	@./$(BIN_DIR)/$(BIN_NAME)

fmt:
	@astyle --style=google -nr *.cpp,*.hpp

doc:
	@doxygen Doxyfile

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
	@echo "Cleaning..."
	@echo ""
	@cat .art/maid.ascii
	@rm -rd $(BUILD_DIR)/* 
	@rm -rd $(BIN_DIR)/*
	@rm -rd $(DOC_DIR)/*
	@echo ""
	@echo "...✓ done!"
