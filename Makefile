CC = gcc
CFLAGS = -Wall -Wextra -O2

all: number_strings_to_hex_array

number_strings_to_hex_array: number_strings_to_hex_array.c
	$(CC) $(CFLAGS) -o number_strings_to_hex_array number_strings_to_hex_array.c

clean:
	rm -f number_strings_to_hex_array
