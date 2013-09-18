CC      := gcc

CFLAGS  := -W -Wall -Werror -I./src/
LDFLAGS := -lunstable -lpenetra

BIN     := penetra

SRC := src/main.c src/dissect.c src/util.c
OBJ := $(patsubst %.c,%.o,$(SRC))

%.o: %.c
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

all: $(OBJ)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(OBJ)

clean:
		$(RM) $(BIN) $(OBJ) *.o $(LIB)
