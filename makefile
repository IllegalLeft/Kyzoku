TARGET 	= kyzoku
SOURCES = src/
LIBS 	= -lm -lSDLmain -lSDL  -lSDL_image -lSDL_mixer -lSDL_ttf
CC 		= gcc
CFLAGS 	= -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default


CFILES = $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SOURCES)*.c))

HEADERS = $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.h)))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SOURCES)$< -o $(SOURCES)$@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(SOURCES)*.o
	-rm -f $(TARGET)
