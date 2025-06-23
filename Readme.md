# number_strings_to_hex_array

A simple utility that reads number strings (decimal, octal, or hexadecimal, space/comma-separated), parses them according to common C conventions, and outputs their bytes as a concatenated C hex array.

## Features

- Accepts multiple numbers, separated by spaces and/or commas.
- Automatically detects number base using these rules:
  - Strings starting with `0` are octal.
  - Strings starting with `0x`, `x`, or `X` are hexadecimal.
  - Any string containing `a`-`f` is hexadecimal (case insensitive).
  - All others are decimal.
- Concatenates all values into a single output array.
- Prints both the array and its length as `const size_t`.

## Build

```sh
make
```

## Usage

```sh
./number_strings_to_hex_array
```

Enter your number string(s) at the prompt (e.g., `0x1A, 1234, 077, xFF, 1e4b`), and the program will output a C array:

```c
const size_t hexArray_len = 8;
unsigned char hexArray[8] = { 0x00, 0x1A, 0x04, 0xD2, 0x3F, 0xFF, 0x1E, 0x4B };
```

## License

MIT
