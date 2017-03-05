TARGET = pe09
GCC = gcc
CFLAGS = -g -Wall -Wshadow  
CC = $(GCC) $(CFLAGS) 
SRCS = pe09.c  answer09.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pe09

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
