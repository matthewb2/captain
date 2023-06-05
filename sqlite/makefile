CC=gcc
CFLAGS=-I.
DEPS = sqlite3.h sqlite3ext.h
OBJ = shell.o sqlite3.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sqlite: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)