NAME := tcpsend
SRCS := src/main.cpp

CC := gcc
CXX := g++
LD := $(CXX)
CFLAGS := -O3
CXXFLAGS := -O3

OBJS := $(SRCS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)
DEPS := $(SRCS:%.c=%.d)
DEPS := $(DEPS:%.cpp=%.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(info OBJS = $(OBJS))
	$(LD) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -MMD -MP -MF $(<:%.c=%.d) -c $< -o $(<:%.c=%.o)

.cpp.o:
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(<:%.cpp=%.d) -c $< -o $(<:%.cpp=%.o)

.PHONY: clean
clean:
	rm -f $(NAME) src/*.o src/*.d

.PHONY: run
run:
	./$(NAME)

-include $(DEPS)

