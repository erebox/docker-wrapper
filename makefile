# Makefile per docker-wrapper - compatibile con sh/bash (MinGW, MSYS, w64devkit)

BIN_DIR := bin
SRC_DIR := src
RES_DIR := res
OBJ_DIR := obj

TARGET	= $(BIN_DIR)/docker.exe
SRC		= $(SRC_DIR)/docker.cpp
RES		= $(RES_DIR)/docker.rc
RES_OBJ	= $(OBJ_DIR)/docker_res.o

CXX		:= g++
CXXFLGS	:= -O2 -s -static
RC		:= windres
RCFLGS	:= -O coff

# Regole

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(RES_OBJ): $(RES)
	$(RC) $(RCFLGS) $< -o $@

$(TARGET): $(SRC) $(RES_OBJ)
	$(CXX) $(CXXFLGS) $^ -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*.exe

distclean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean distclean dirs