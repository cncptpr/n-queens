#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// #define DBG_DIAG_INDEXS
// #define DBG_SOLVE_STEPS
// #define DBG_COORD_INFO

int xy_to_ddown(int x, int y, int n) { return (y - x) + n - 1; }
int xy_to_dup(int x, int y, int n) { return (n - y - x) + n - 2; }

typedef struct {
  int n, *x, *y, *dup, *ddown;
} Field;

int is_free(Field field, int x, int y) {
  return !field.x[x] && !field.y[y] && !field.dup[xy_to_dup(x, y, field.n)] &&
         !field.ddown[xy_to_ddown(x, y, field.n)];
}
void assign(Field field, int x, int y, int value) {
  field.x[x] = field.y[y] = field.dup[xy_to_dup(x, y, field.n)] =
      field.ddown[xy_to_ddown(x, y, field.n)] = value;
}

int solve(int x, Field field) {
#ifdef DBG_SOLVE_STEPS
  printf("%d\n", x);
  for (int x = 0; x < field.n; x++) {
    for (int y = 0; y < field.n; y++) {
      if (field.x[x] != 0 && field.x[x] == field.y[y])
        printf("%2d ", field.x[x]);
      else
        printf(" 0 ");
    }
    printf("\n");
  }
  printf("\n");
#endif // DBG_SOLVE_STEPS
  if (field.n == x)
    return 1;
  for (int y = 0; y < field.n; y++) {
    if (is_free(field, x, y)) {
      assign(field, x, y, x + 1); // block
      if (solve(x + 1, field)) {
        return 1;
      }
      assign(field, x, y, 0); // unblock
    }
  }
  return 0;
}

#ifdef DBG_DIAG_INDEXS
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: n-queens <n>\n");
    return 0;
  }
  int n = atoi(argv[1]);
  if (!n) {
    printf("Error: %s is not a valide value vor n\n", argv[1]);
    printf("usage: n-queens <n>\n");
    return 1;
  }
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++)
      printf("(%d, %d):%2d ", x, y, xy_to_ddown(x, y, n));
    printf("\n");
  }
  printf("\n");
  printf("\n");
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++)
      printf("(%d, %d):%2d ", x, y, xy_to_dup(x, y, n));
    printf("\n");
  }
}
#else

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: n-queens <n>\n");
    return 0;
  }
  int n = atoi(argv[1]);
  if (!n) {
    printf("Error: %s is not a valide value vor n\n", argv[1]);
    printf("usage: n-queens <n>\n");
    return 1;
  }
  Field field = {
      .n = n,
      .x = calloc(n, sizeof(int)),
      .y = calloc(n, sizeof(int)),
      .dup = calloc(2 * n - 1, sizeof(int)),
      .ddown = calloc(2 * n - 1, sizeof(int)),
  };

  assert(solve(0, field));

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (field.x[x] != 0 && field.x[x] == field.y[y])
#ifdef DBG_COORD_INFO
        printf("(%2d, %2d, %2d, %2d) q", field.x[x], field.y[y],
               field.dup[xy_to_dup(x, y, n)],
               field.ddown[xy_to_ddown(x, y, n)]);
      else
        printf("(%2d, %2d, %2d, %2d) .", field.x[x], field.y[y],
               field.dup[xy_to_dup(x, y, n)],
               field.ddown[xy_to_ddown(x, y, n)]);
#else
        printf("q ");
      else
        printf(". ");
#endif
    }
    printf("\n");
  }
}
#endif
