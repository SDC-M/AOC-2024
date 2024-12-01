#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
  long long int value;
  struct cell *next;
} cell;

// Attempts to create a new cell with the value given as parameter. On failure
// returns nullptr otherwise a pointer to the new cell.
cell *new_cell(int x) {
  cell *p = malloc(sizeof *p);
  if (p == nullptr) {
    return nullptr;
  }
  p->value = x;
  p->next = nullptr;
  return p;
}

// Attempts to create a new cell with the value given as parameter and insert it
// at the top of simply chained list. On failure returns nullptr otherwise a
// pointer to the new cell.
cell *insert_head(cell **head, int value) {
  cell *p = new_cell(value);
  if (p == nullptr) {
    return nullptr;
  }
  p->next = *head;
  *head = p;
  return p;
}

// Frees all resources linked to the head pointer.
void dispose(cell *head) {
  while (head != nullptr) {
    cell *t = head;
    head = head->next;
    free(t);
  }
}

// Returns the sum of the differences between two values ​​in a list at the same
// index.
long long int diff_list(cell *l1, cell *l2) {
  cell *ll1 = l1;
  cell *ll2 = l2;
  long long int sum = 0;
  while (ll1 != nullptr && ll2 != nullptr) {
    if ((ll1->value) >= (ll2->value)) {
      sum += (ll1->value) - (ll2->value);
    } else {
      sum += (ll2->value) - (ll1->value);
    }
    ll1 = ll1->next;
    ll2 = ll2->next;
  }
  return sum;
}

// Sorts by ascending insertion a list pointed to by *head and returns a pointer
// to that sorted list.
void insertion_sort(cell **head) {
  if (*head == nullptr || (*head)->next == nullptr) {
    return;
  }
  cell *sorted = nullptr;
  cell *current = *head;
  while (current != nullptr) {
    cell *next = current->next;
    if (sorted == nullptr || sorted->value >= current->value) {
      current->next = sorted;
      sorted = current;
    } else {
      cell *temp = sorted;
      while (temp->next != nullptr && temp->next->value < current->value) {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }
  *head = sorted;
}

// Each number from the left list appears in the right list. Calculate a total
// similarity score by adding up each number in the left list after multiplying
// it by the number of times that number appears in the right list.
long long int similarity_score(cell *l1, cell *l2) {
  cell *ll1 = l1;
  cell *ll2 = l2;
  long long int result = 0;
  while (ll1 != nullptr) {
    cell *lll2 = ll2;
    long long int nb_occ_right = 0;
    while (lll2 != nullptr) {
      if (ll1->value == lll2->value) {
        nb_occ_right += 1;
      }
      lll2 = lll2->next;
    }
    result += (ll1->value) * nb_occ_right;
    ll1 = ll1->next;
  }
  return result;
}

// Create two simply linked lists pointed by l1 and l2. Once in two. The value
// read on the standard input is inserted at the head of l1 and the other time
// at the head of l2. Performs sort by ascending insertion on each of the two
// lists then calculates the sum of the differences between the two lists for
// each element at the same index.
int main() {
  int r = 0;
  cell *l1 = nullptr;
  cell *l2 = nullptr;
  int value;
  int k = 0;
  while (scanf("%d", &value) != EOF) {
    if (k % 2 == 0) {
      if (insert_head(&l1, value) == nullptr) {
        r = -1;
        goto dispose;
      }
    } else {
      if (insert_head(&l2, value) == nullptr) {
        r = -1;
        goto dispose;
      }
    }
    ++k;
  }
  insertion_sort(&l1);
  insertion_sort(&l2);
  printf("Étape 1 :%lld\n", diff_list(l1, l2));
  printf("Étape 2 :%lld\n", similarity_score(l1, l2));
dispose:
  dispose(l1);
  dispose(l2);
  if (r == 0) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
