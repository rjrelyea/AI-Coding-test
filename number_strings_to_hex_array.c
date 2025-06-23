#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Max number of input strings and total output bytes
#define MAX_STRINGS 64
#define MAX_BYTES 256

// Helper to check if string contains any hex letter
int contains_hex_letter(const char *s) {
    while (*s) {
        char c = tolower((unsigned char)*s);
        if (c >= 'a' && c <= 'f') return 1;
        s++;
    }
    return 0;
}

// Parse string to value and get bytes (big-endian)
int parse_and_fill_bytes(const char *in, unsigned char *out) {
    // Skip leading whitespace
    while (*in && isspace((unsigned char)*in)) in++;
    // Copy and lowercase for checks
    char buf[256];
    int i = 0;
    for (; in[i] && i<255; i++) buf[i] = tolower((unsigned char)in[i]);
    buf[i] = 0;

    int base = 10;
    const char* parse_ptr = in;
    if (buf[0] == '0' && buf[1] == 'x') {
        base = 16;
    } else if (buf[0] == 'x') {
        base = 16;
        parse_ptr = in + 1;
    } else if (contains_hex_letter(buf)) {
        base = 16;
    } else if (buf[0] == '0') {
        base = 8;
    }
    unsigned long value = strtoul(parse_ptr, NULL, base);

    // Fill bytes big-endian (most significant first)
    unsigned char tmp[sizeof(unsigned long)];
    int byte_count = 0;
    unsigned long t = value;
    do {
        tmp[byte_count++] = t & 0xFF;
        t >>= 8;
    } while (t && byte_count < (int)sizeof(unsigned long));
    // Copy in big-endian order
    for (int j = 0; j < byte_count; ++j)
        out[j] = tmp[byte_count - 1 - j];
    return byte_count;
}

int main() {
    char input[1024];
    printf("Enter number strings (separated by spaces and/or commas):\n");
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error reading input.\n");
        return 1;
    }

    unsigned char hexArray[MAX_BYTES];
    int total_bytes = 0;

    // Tokenize by space and/or comma
    const char *delim = " ,\t\r\n";
    char *token = strtok(input, delim);
    while (token) {
        int bytes = parse_and_fill_bytes(token, hexArray + total_bytes);
        total_bytes += bytes;
        if (total_bytes > MAX_BYTES) {
            printf("Error: too much data!\n");
            return 1;
        }
        token = strtok(NULL, delim);
    }

    printf("const size_t hexArray_len = %d;\n", total_bytes);
    printf("unsigned char hexArray[%d] = { ", total_bytes);
    for (int i = 0; i < total_bytes; ++i) {
        printf("0x%02X", hexArray[i]);
        if (i < total_bytes - 1) printf(", ");
    }
    printf(" };\n");

    return 0;
}
