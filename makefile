CC = gcc

SRC = main.c bitmap.c perlin.c
OBJ = $(SRC:.c=.o)
EXEC = perlin

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJ)