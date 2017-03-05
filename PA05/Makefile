TARGET = pa05
GCC = gcc
CFLAGS = -g -Wall -Wshadow  
CC = $(GCC) $(CFLAGS) 
SRCS = pa05.c  bmp.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pa05

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
