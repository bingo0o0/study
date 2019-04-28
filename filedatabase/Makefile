TARGET := filedatabase


CROSS :=

CC := $(CROSS)gcc
CXX := $(CROSS)g++
CFLAGS += -g -Wall


SRC_S += $(wildcard *.cpp)
OBJ_S := $(patsubst %.cpp, %.o, $(SRC_S))



all:$(OBJ_S)
	@echo "nothing"


%.o : %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY:chean
clean:
	@rm -f $(OBJ_S)