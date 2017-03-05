TARGET = pe11
GCC = gcc
CFLAGS = -g -Wall -Wshadow  
CC = $(GCC) $(CFLAGS) 
SRCS = pe11.c  bmp.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pe11

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
