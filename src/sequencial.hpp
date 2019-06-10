#include <omp.h>
#include <vector>
#include <mutex>    

namespace sequencial {
void heap_sort(int a[], int count);
void parallel_heap_sort(int **arr, int size, int threads, int **tmp);
void parallel_heap_sort_with_lock(int **arr, int size, int threads, int **tmp);
}  // namespace sequencial
