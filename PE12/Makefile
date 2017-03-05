TARGET = pe12
GCC = gcc
CFLAGS = -g -Wall -Wshadow  
CC = $(GCC) $(CFLAGS) 
SRCS = pe12.c  bmp.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pe12

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
