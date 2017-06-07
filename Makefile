CC = gcc
CFLAGS = -Wall -std=c99
OUTFILE = main.exe
OBJS = list.o main.o
SRCS = list.c main.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
