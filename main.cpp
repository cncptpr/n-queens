#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// #define DBG_DIAG_INDEXS
// #define DBG_SOLVE_STEPS
// #define DBG_QUEEN_INFO
// #define DBG_COORD_INFO

struct Coord {
  unsigned int x, y;
  Coord(unsigned int x, unsigned int y) : x(x), y(y) {};
};

enum Diag : bool {
  UP = true,
  DOWN = false,
};

template <Diag diag> class DiagArray {
  unsigned int n;
  unsigned int *array;

#ifdef DBG_QUEEN_INFO
public:
#endif // DBG_QUEEN_INFO

  unsigned int idx(const Coord &c) {
    if (diag == UP)
      return (c.y - c.x) + n - 1;
    return (n - c.y - c.x) + n - 2;
  }

public:
  DiagArray(unsigned int n) : n(n), array(new unsigned int[2 * n - 1]) {};
  unsigned int &operator[](Coord c) { return array[idx(c)]; }
};

class Field {
  unsigned int *x, *y;
  DiagArray<UP> dup;
  DiagArray<DOWN> ddown;

  bool solve(unsigned int x);

public:
  const unsigned int n;

  Field(unsigned int n)
      : n(n), x(new unsigned int[n]), y(new unsigned int(n)), dup(n), ddown(n) {
    for (int i = 0; i < n; i++)
      x[i] = y[i] = 0;
  }

  bool solve();

  bool is_free(Coord c) { return !x[c.x] && !y[c.y] && !dup[c] && !ddown[c]; }
  bool is_free(unsigned int x, unsigned int y) { return is_free(Coord(x, y)); }

  void assign(unsigned int x, unsigned int y, unsigned int value) {
    assign(Coord(x, y), value);
  }
  void assign(Coord c, unsigned int value) {
    x[c.x] = y[c.y] = dup[c] = ddown[c] = value;
  }

  void print() {
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        if (this->x[x] != 0 && this->x[x] == this->y[y])
#ifdef DBG_QUEEN_INFO
          printf("(%2d, %2d, %2d, %2d) q", this->x[x], this->y[y],
                 this->dup[Coord(x, y)], this->ddown[Coord(x, y)]);
        else
          printf("(%2d, %2d, %2d, %2d) .", this->x[x], this->y[y],
                 this->dup[Coord(x, y)], this->ddown[Coord(x, y)]);
#elif defined(DBG_COORD_INFO)
          printf("(%2d, %2d) q", x, y);
        else
          printf("(%2d, %2d) .", x, y);
#else
          printf("q ");
        else
          printf(". ");
#endif
      }
      printf("\n");
    }
    printf("\n");
  }
};

class Cell : public Coord {
  Field &field;

public:
  using Coord::Coord;
  Cell(Field &field, unsigned int x, unsigned int y)
      : field(field), Coord(x, y) {
    if (!(x < field.n && y < field.n))
      throw "Coord out of bounds";
  }
  void operator=(unsigned int value) { field.assign(x, y, value); }
  operator bool() const { return !field.is_free(x, y); }
};

bool Field::solve(unsigned int x) {
#ifdef DBG_SOLVE_STEPS
  field.print();
#endif // DBG_SOLVE_STEPS
  if (n == x)
    return true;
  for (int y = 0; y < n; y++) {
    Cell cell(*this, x, y);
    if (!cell) {
      cell = x + 1; // block
      if (solve(x + 1)) {
        return true;
      }
      cell = false; // unblock
    }
  }
  return false;
}
bool Field::solve() { return solve(0); }

#ifdef DBG_DIAG_INDEXS
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: n-queens <n>\n");
    return 0;
  }
  unsigned int n = atoi(argv[1]);
  if (!n) {
    printf("Error: %s is not a valide value vor n\n", argv[1]);
    printf("usage: n-queens <n>\n");
    return 1;
  }
  DiagArray<UP> up(n);
  DiagArray<DOWN> down(n);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++)
      printf("(%d, %d):%2d ", x, y, up.idx(Coord(x, y)));
    printf("\n");
  }
  printf("\n");
  printf("\n");
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++)
      printf("(%d, %d):%2d ", x, y, down.idx(Coord(x, y)));
    printf("\n");
  }
}
#else

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: n-queens <n>" << std::endl;
    return 0;
  }
  try {
    unsigned int n = std::stoi(argv[1]);
    Field field(n);
    assert(field.solve());
    field.print();
    return 0;
  } catch (std::invalid_argument const &ex) {
    std::cout << "Error: " << argv[1] << " is not a valide value vor n\n"
              << "usage: n-queens <n>" << std::endl;
    return 1;
  } catch (std::out_of_range const &ex) {
    std::cout << "n can't be negative. Or too big." << std::endl;
    return 1;
  };
}
#endif
