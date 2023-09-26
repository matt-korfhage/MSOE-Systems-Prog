CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lncurses
SOURCES=snake.c field.c game.c score_file.c arguments_parser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=snake
all: $(SOURCES) $(EXECUTABLE)
# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d