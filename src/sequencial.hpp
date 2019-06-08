#include <omp.h>
#include <vector>

namespace sequencial {
void heap_sort(int a[], int count);
void parallel_heap_sort(int **arr, int size, int threads, int **tmp);
}  // namespace sequencial
