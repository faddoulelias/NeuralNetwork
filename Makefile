.PHONY = all clean run

# Compiler
CXX := g++
CFLAGS := -Wall -Wextra -Wpedantic -Werror -W -g -std=c++17 -I./src/headers

# Directories
BUILD  := ./build
OBJECT := ./build/obj
SOURCE := ./src
HEADER := ./src/headers

# Files
SRCS := $(wildcard $(SOURCE)/*.cpp)
OBJS := $(patsubst $(SOURCE)/%.cpp, $(OBJECT)/%.o, $(SRCS))
EXEC := $(BUILD)/Matrix.exe

# Makefile commands
all : $(EXEC)

run:$(EXEC)
	$(EXEC) $(ARGS)

$(EXEC) : $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJECT)/%.o : $(SOURCE)/%.cpp
	@IF NOT EXIST "$(OBJECT)" mkdir "$(OBJECT)"
	$(CXX) $(CFLAGS) -o $@ -c $^

clean:
	rmdir /s /q "$(BUILD)"

