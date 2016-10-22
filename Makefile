CC=gcc
CFLAGS=-c -Wall -Wno-format -Wno-char-subscripts -pipe -O3 -flto -DNDEBUG
LDFLAGS=-flto
SOURCES=attacked.c fen.c magic.c main.c makemove.c movegen.c movesort.c perft.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dorpsgek

.PHONY: all clean test

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

test: $(EXECUTABLE)
	cat ./perft-$(TEST).epd | ./dorpsgek

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
