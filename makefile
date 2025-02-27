##
# turtix
#
# @file
# @version 0.1

# Project structure
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
VENDOR_DIR = vendor

# SFML configuration
SFML_VERSION = 2.6.1
SFML_DIR = $(VENDOR_DIR)/SFML-$(SFML_VERSION)
SFML_INCLUDE = $(SFML_DIR)/include
SFML_LIB = $(SFML_DIR)/lib

# Get absolute path to SFML lib directory for rpath
SFML_LIB_ABS = $(shell pwd)/$(SFML_LIB)

# Compiler flags
CFLAGS = -c -Wall -Wextra -I$(SFML_INCLUDE)
# Add rpath to the linker flags so the executable can find the libraries at runtime
LFLAGS = -Wall -Wextra -L$(SFML_LIB) -Wl,-rpath,$(SFML_LIB_ABS) -lsfml-graphics -lsfml-window -lsfml-system

TARGET = turtix

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

all: sfml $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR) sfml
	$(CXX) $(CFLAGS) -o $@ $<

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(VENDOR_DIR):
	mkdir -p $@

# Download and extract SFML
sfml: | $(VENDOR_DIR)
	@if [ ! -d "$(SFML_DIR)" ]; then \
		echo "Downloading SFML $(SFML_VERSION)..."; \
		mkdir -p $(SFML_DIR); \
		wget -q https://www.sfml-dev.org/files/SFML-$(SFML_VERSION)-linux-gcc-64-bit.tar.gz -O sfml.tar.gz; \
		tar -xzf sfml.tar.gz -C $(VENDOR_DIR); \
		mv $(VENDOR_DIR)/SFML-$(SFML_VERSION)/* $(SFML_DIR)/; \
		rmdir $(VENDOR_DIR)/SFML-$(SFML_VERSION); \
		rm sfml.tar.gz; \
		echo "SFML $(SFML_VERSION) downloaded and extracted."; \
	else \
		echo "SFML $(SFML_VERSION) already exists."; \
	fi

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

clean-all: clean
	rm -rf $(VENDOR_DIR)

.PHONY: all clean clean-all sfml
