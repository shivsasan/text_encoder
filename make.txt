# final executable to build:
TARGET= encode
# .o files to link in (for all .c files)
OBJS = encode.o

# Add support for pthread and real-time clock here:
CXXFLAGS  = -Wall -Werror -Wextra -pedantic -ansi

# You should not need to change any of this:
CC = g++

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f outputFile.txt