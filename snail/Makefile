AR = ar
CXX := /usr/local/bin/g++-HEAD
CXX_FLAGS = -Wall -Wextra -g -O0 -MMD -DDEBUG -std=c++17 -I/usr/local/include
BIN_DIR = bin
SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJECTS = $(foreach i, $(SOURCES), $(BIN_DIR)/$(basename $(i)).o)
LIB = ./snail.a


MKDIR := mkdir


.PHONY: build clean rebuild


all: build



build: $(LIB)


$(LIB): $(OBJECTS)
	$(AR) r $@ $^


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(BIN_DIR):
	$(MKDIR) -p $(BIN_DIR)/detail


clean:
	-@$(RM) -f $(PROGRAM)
	-@$(RM) -f $(BIN_DIR)/*.d $(BIN_DIR)/*.o


rebuild: clean build


-include $(BIN_DIR)/*.d
