sinclude config.make
sinclude config.build

CC = g++
TARGET = git-bin
PREFIX = /usr/local/bin

# Directories
INCLUDE_DIR = include
TESTS_DIR = testsuite
BUILD_DIR = build
SRC_DIR = src
BIN_DIR = bin

INCLUDES = -Iinclude -Icommon/include
LIBS = -g -ggdb -lrt -lPocoFoundation -lPocoUtil
CFLAGS = -Wno-write-strings $(INCLUDES) $(LIBS) -std=c++11
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS	= $(patsubst %,$(BUILD_DIR)/%.o, $(subst src/,,$(subst .cpp,,$(SOURCES))))

# Test Objects
TESTS = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst %,$(BUILD_DIR)/$(TESTS_DIR)/%.o, $(subst $(TESTS_DIR)/,,$(subst .cpp,,$(TESTS))))
TEST_OBJECTS += $(subst $(BUILD_DIR)/main.o,,$(OBJECTS))

.PHONY: all clean
DEFAULT = all

all: git-bin tests
git-bin: directories
git-bin: $(BIN_DIR)/$(TARGET)	
tests: directories
tests: $(BIN_DIR)/$(TARGET)-test

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(TESTS_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	@rm -f $(BIN_DIR)/$(TARGET)
	@rm -f $(BIN_DIR)/$(TARGET)-test
	@rm -f $(BUILD_DIR)/*.o
	@rm -f $(BUILD_DIR)/$(TESTS_DIR)/*.o

mrproper:
	@rm -rf $(BUILD_DIR) 
	@rm -rf $(BIN_DIR)

install: git-bin
	@cp $(BIN_DIR)/$(TARGET) $(PREFIX)/

uninstall:
	@rm -f $(PREFIX)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) -Wall $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp
	$(CC) -Wall $(CFLAGS) -c $< -o $@

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

$(BIN_DIR)/$(TARGET)-test: $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -Wall $(LIBS) -lcppunit -o $@
