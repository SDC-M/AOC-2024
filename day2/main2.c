#include <stdio.h>
#include <stdlib.h>

#define LENGTH_MAX 100

// Takes as parameter an array of integers t and its size nmemb and returns 0 if
// the sequence of integers contained in the array t is strictly increasing and
// the difference between two consecutive integers is between 1 and 3 limits
// inclusive, -1 otherwise.
int is_well_increasing(int t[LENGTH_MAX], size_t nmemb) {
  if (nmemb < 2) {
    return -1;
  }
  int result = 0;
  for (size_t k = 0; k < nmemb - 1; ++k) {
    if (t[k] >= t[k + 1]) {
      result = -1;
      break;
    }
    if (t[k + 1] - t[k] > 3) {
      result = -1;
      break;
    }
  }
  return result;
}

// Takes as parameter an array of integers t and its size nmemb and returns 0 if
// the sequence of integers contained in the array t is strictly decreasing and
// the difference between two consecutive integers is between 1 and 3 limits
// inclusive, -1 otherwise.
int is_well_decreasing(int t[LENGTH_MAX], size_t nmemb) {
  int result = 0;
  for (size_t k = 0; k < nmemb - 1; ++k) {
    if (t[k] <= t[k + 1]) {
      result = -1;
      break;
    }
    if (t[k] - t[k + 1] > 3) {
      result = -1;
      break;
    }
  }
  return result;
}

// Analyzes each line read from the standard input until exhaustion or error, if
// it is composed of integers we then store them in a table, we see if the
// sequence respects the rules if yes we increment the value of the total
// result.
int main() {
  int r = EXIT_SUCCESS;
  char *w = malloc(LENGTH_MAX + 1);
  if (w == nullptr) {
    goto errors;
  }
  int x;
  int t[LENGTH_MAX];
  size_t k = 0;
  int result = 0;
  while (fgets(w, LENGTH_MAX, stdin) != nullptr) {
    char *p = w;
    while (sscanf(p, "%d", &x) == 1) {
      while (*p != '\0' && *p != ' ') {
        p++;
      }
      if (*p != '\0') {
        p++;
      }
      t[k] = x;
      ++k;
    }
    if (is_well_decreasing(t, k) != -1 || is_well_increasing(t, k) != -1) {
      result += 1;
    }
    k = 0;
  }
  printf("%d\n", result);
errors:
  if (!feof(stdin)) {
    r = EXIT_FAILURE;
  }
  free(w);
  return r;
}
