CC = clang 
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
EXEC = sorting
OBJS = sorting.o quick.o batcher.o heap.o shell.o set.o stats.o  

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
