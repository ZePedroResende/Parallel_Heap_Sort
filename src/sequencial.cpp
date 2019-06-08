#include "sequencial.hpp"

namespace sequencial {

void siftDown(int a[], int start, int end) {
  int root = start;
  while ((2 * root + 1) <= end) {
    int child = 2 * root + 1;
    int swap = root;
    if (a[swap] < a[child]) swap = child;
    if ((child + 1) <= end)
      if (a[swap] < a[child + 1]) swap = child + 1;
    if (swap == root)
      root = end;  // return
    else {
      int tmp = a[swap];
      a[swap] = a[root];
      a[root] = tmp;
      root = swap;
    }
  }
}
void heapify(int *a, int count) {
  int start = (count - 1) / 2;
  while (start >= 0) {
    siftDown(a, start, count - 1);
    start--;
  }
}

void heap_sort(int a[], int count) {
  heapify(a, count);
  // buildmax - heap(sequential)
  int end = count - 1;
  while (end > 0) {
    // do in parallel// do in sequentialorder
    int cmax = a[0];
    a[0] = a[end];
    a[end] = cmax;  // swap
    end--;          // decreaseheapsize// repairheap: do
    // withlockingofparentandchild
    siftDown(a, 0, end);
  }
}

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
void parallel_heap_sort(int **arr, int size, int threads, int **tmp) {
  int small_part = 50000;
  omp_set_num_threads(threads);

#pragma omp parallel for schedule(dynamic, 1000)
  for (int i = 0; i < size; i += small_part) {
    int s = std::min(small_part, size - i);
    heap_sort(*arr + i, s);
  }

  for (int i = small_part; i < size; i *= 2) {
#pragma omp parallel for schedule(dynamic, 1000)
    for (int j = 0; j < size; j = j + 2 * i) {
      int r = j + i;
      int n1 = std::max(0, std::min(i, size - j));
      int n2 = std::max(0, std::min(i, size - r));

      int ind1 = 0, ind2 = 0, k;

      for (k = 0; k < n1; k++) {
        (*tmp)[j + k] =
            (ind1 >= n1)
                ? (*arr)[r + ind2++]

                : (ind2 >= n2 || less_then((*arr)[j + ind1], (*arr)[r + ind2]))
                      ? (*arr)[j + ind1++]

                      : (*arr)[r + ind2++];
      }

      ind1 = n1 - 1, ind2 = n2 - 1;

      for (k = n1 + n2 - 1; k >= n1; k--) {
        (*tmp)[j + k] =
            (ind1 < 0)
                ? (*arr)[r + ind2--]

                : (ind2 < 0 || greater_then((*arr)[j + ind1], (*arr)[r + ind2]))
                      ? (*arr)[j + ind1--]

                      : (*arr)[r + ind2--];
      }
    }
    int *buf = *arr;
    *arr = *tmp;
    *tmp = buf;
  }
}

}  // namespace sequencial
