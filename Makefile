CC = clang
CFLAGS = -Wall -Wextra -std=c99
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

minicel: $(OBJECTS)
	$(CC) -O3 -o $@ $^ $(LDFLAGS)

minicel-debug: $(OBJECTS) tokenize.c
	$(CC) -gfull -S -O1 -save-temps -fsanitize=address -o $@ $^ $(LDFLAGS)

tokenize.s: tokenize.c
	$(CC) $(CFLAGS) -O1 -gfull -S -o $@ $<

.PHONY: clean

clean:
	rm -rf minicel minicel-debug $(OBJECTS) *.i *.s *.bc
