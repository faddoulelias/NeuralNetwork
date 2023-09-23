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

define compile
	@IF NOT EXIST "$(OBJECT)" mkdir "$(OBJECT)"
	@echo [ Compiling	] $(1)
	@$(CXX) $(CFLAGS) -o $(2) -c $(1)
endef

define link
	@echo [ Linking	] $(1)
	@$(CXX) $(CFLAGS) -o $(1) $(2)
endef

define run
	@echo [ Running	] $(1)
	@echo.
	@$(1)
endef

# Makefile commands
all : $(EXEC)

run:$(EXEC)
	$(call run,$^)

$(EXEC) : $(OBJS)
	$(call link,$@,$^)

$(OBJECT)/%.o : $(SOURCE)/%.cpp
	$(call compile,$^,$@)

clean:
	rmdir /s /q "$(BUILD)"

