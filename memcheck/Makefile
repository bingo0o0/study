TARGET := libwrapalloc.a

CROSS := arm-hisiv500-linux-uclibcgnueabi-
CC := $(CROSS)gcc
CXX := $(CROSS)g++
AR := $(CROSS)ar


IFLAGS += -I./include

SRC :=  ./src/memcheck.c
objs = $(patsubst %.c, %.o, $(SRC))

TEST_SRC := ./src/test.cpp
TEST_OBJ := $(patsubst %.cpp, %.o, $(TEST_SRC))


CFLAGS += -g -Wall
LDFLAGS += -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=free


all:clean $(TARGET) test

$(TARGET):$(objs)
	$(AR) -rv $@ $^
	

test:$(TEST_OBJ) $(TARGET)
	$(CXX) $^  $(LDFLAGS) -static -o $@
	

%.o:%.c
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@
	
%.o:%.cpp
	$(CXX) $(IFLAGS) $(CFLAGS) -c $< -o $@
	
	
	
.PYTHON:clean
clean:
	@echo -e "\e[31mcleaning ... \e[m"
	@rm -f test
	@rm -f $(objs)
	@rm -f $(TARGET)
	@rm -f $(TEST_OBJ)