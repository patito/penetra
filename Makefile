CC      := gcc

CFLAGS  := -W -Wall -Werror -I./src/ -I/usr/local/include -L/usr/local/lib
LDFLAGS := -lunstable -lpenetra

BIN     := penetra

SRC := src/main.c src/dissect.c src/util.c
OBJ := $(patsubst %.c,%.o,$(SRC))

%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJ)
		$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(BIN) $(OBJ) *.o $(LIB)
