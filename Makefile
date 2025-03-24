CC = gcc
CFLAGS = -Wall

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: main
	@./$<

main: $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm *.exe
	@rm *.o