#include "parallel.hpp"

bool less_then(const int a, const int b) {
  if (a == -1 && b != -1) return true;
  if (b == -1) return false;

  return (a < b);
}

bool greater_then(const int &a, const int &b) {
  if (b == -1 && a != -1) return true;
  if (a == -1) return false;

  return (a > b);
}

int omp_sort(int **a, int size, int **tmp) {
  int threads = omp_get_max_threads();
  omp_set_nested(1);
  DHsort(a, size, threads, tmp);

  return 0;
}

void DHsort(int **arr, int size, int threads, int **tmp) {
  int small_part = 50000;
  omp_set_num_threads(threads);

#pragma omp parallel for schedule(dynamic, 1000)
  for (int i = 0; i < size; i += small_part) {
    int s = min(small_part, size - i);
    make_heap(*arr + i, *arr + i + s);
    sort_heap(*arr + i, *arr + i + s);
  }

  for (int i = small_part; i < size; i *= 2) {
#pragma omp parallel for schedule(dynamic, 1000)
    for (int j = 0; j < size; j = j + 2 * i) {
      int r = j + i;
      int n1 = max(0, min(i, size - j));
      int n2 = max(0, min(i, size - r));

      int ind1 = 0, ind2 = 0, k;

      for (k = 0; k < n1; k++) {
        if (ind1 >= n1)
          (*tmp)[j + k] = (*arr)[r + ind2++];

        else if (ind2 >= n2)
          (*tmp)[j + k] = (*arr)[j + ind1++];

        else if (less_then((*arr)[j + ind1], (*arr)[r + ind2]))
          (*tmp)[j + k] = (*arr)[j + ind1++];

        else
          (*tmp)[j + k] = (*arr)[r + ind2++];
      }

      ind1 = n1 - 1, ind2 = n2 - 1;

      for (k = n1 + n2 - 1; k >= n1; k--) {
        if (ind1 < 0)
          (*tmp)[j + k] = (*arr)[r + ind2--];

        else if (ind2 < 0)
          (*tmp)[j + k] = (*arr)[j + ind1--];

        else if (greater_then((*arr)[j + ind1], (*arr)[r + ind2]))
          (*tmp)[j + k] = (*arr)[j + ind1--];

        else
          (*tmp)[j + k] = (*arr)[r + ind2--];
      }
    }
    int *buf = *arr;
    *arr = *tmp;
    *tmp = buf;
  }
}
