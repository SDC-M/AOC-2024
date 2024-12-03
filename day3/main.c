#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 12
#define MIN_BUFFER_SIZE 7

// Returns true if the given character is a digit (0-9).
bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

// Returns true if the first 4 characters are the sequence "mul("
bool is_correct_start(char *s) {
  return s[0] == 'm' && s[1] == 'u' && s[2] == 'l' && s[3] == '(';
}

// Returns the number of digits in the sequence, or -1 if invalid.
size_t how_many_digits(char *s) {
  size_t size = 0;
  while (is_digit(s[size])) {
    ++size;
  }
  return size > 0 && size <= 3 ? size : (size_t) -1;
}

// Returns the size of the valid sequence "mul(X,Y)" or 0 if invalid.
size_t is_correct_sequence(char *s, size_t len) {
  if (len < MIN_BUFFER_SIZE || !is_correct_start(s)) {
    return 0;
  }
  char *p = s + 4;
  size_t size = 4;
  size_t digits1 = how_many_digits(p);
  if (digits1 == (size_t) -1 || size + digits1 >= len) {
    return 0;
  }
  p += digits1;
  size += digits1;
  if (*p != ',') {
    return 0;
  }
  p++;
  size++;
  size_t digits2 = how_many_digits(p);
  if (digits2 == (size_t) -1 || size + digits2 >= len) {
    return 0;
  }
  p += digits2;
  size += digits2;
  if (*p != ')') {
    return 0;
  }
  return size + 1;
}

// Extract the number from the string.
int extract_number(char *s) {
  int number = 0;
  while (is_digit(*s)) {
    number = number * 10 + (*s - '0');
    s++;
  }
  return number;
}

int main() {
  int c;
  char s[MAX_BUFFER_SIZE + 1];
  long long int total = 0;
  size_t buffer_length = 0;
  while ((c = fgetc(stdin)) != EOF) {
    s[buffer_length++] = (char) c;
    s[buffer_length] = '\0';
    if (buffer_length >= MIN_BUFFER_SIZE) {
      size_t size = is_correct_sequence(s, buffer_length);
      if (size > 0) {
        char *p = s + 4;
        int num1 = extract_number(p);
        while (*p != ',') {
          p++;
        }
        p++;
        int num2 = extract_number(p);
        total += num1 * num2;
        memmove(s, s + size, buffer_length - size);
        buffer_length -= size;
      } else if (buffer_length >= MAX_BUFFER_SIZE) {
        memmove(s, s + 1, buffer_length - 1);
        buffer_length--;
      }
    }
  }
  printf("%lld\n", total);
  return EXIT_SUCCESS;
}
