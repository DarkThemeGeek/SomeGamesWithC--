CXX := g++
CXXFLAGS := -Wall -Wextra -O2 -MMD -MP -std=c++23 -g

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := ../include
LIB_DIR := ../lib

TARGET := program

# Add include path
CPPFLAGS := -I$(INCLUDE_DIR)

# Add library path (linker flags)
LDFLAGS := -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)

# Add libraries to link (example: -lmylib)
LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lX11 -lglm

# Find all C++ files recursively
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Convert src/...cpp → build/...o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Dependency files
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)