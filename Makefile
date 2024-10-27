CC = gcc
CFLAGS =
LFLAGS = -lm
TARGET = parasorter
SRCS = main.c list.c
OBJS = $(SRCS:.c=.o)
HEADERS = main.h list.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean