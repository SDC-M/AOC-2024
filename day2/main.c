#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_well_increasing(int t[UCHAR_MAX], size_t nmemb) {
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

int is_well_decreasing(int t[UCHAR_MAX], size_t nmemb) {
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

int main() {
  int r = EXIT_SUCCESS;
  char *w = malloc(UCHAR_MAX + 1);
  if (w == nullptr) {
    goto errors;
  }
  int x;
  int t[UCHAR_MAX];
  size_t k = 0;
  int result = 0;
  while (fgets(w, UCHAR_MAX, stdin) != nullptr) {
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
    for (size_t x = 0; x < k; ++x){
      printf("%d ", t[x]);
    }
    printf("\n");
    if (is_well_decreasing(t, k) != -1) {
      result += 1;
    }
    if (is_well_increasing(t, k) != -1) {
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
