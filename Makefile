CC = gcc
CFLAGS = -Wall -std=c99
OUTFILE = main.exe
OBJS = rc4.o list.o main.o
SRCS = rc4.c list.c main.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
