CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -fsanitize=address -Wno-unused-parameter -Wno-unused-variable
TARGET = calc
SRCS := $(wildcard main.c lib/**/*.c)
OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o build/$(TARGET) $(OBJS)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o build/$(TARGET)
