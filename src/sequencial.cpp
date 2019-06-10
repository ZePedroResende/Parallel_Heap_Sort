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

// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(int arr[], int n, int i) 
{ 
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest]) 
		largest = l; 

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest]) 
		largest = r; 

	// If largest is not root 
	if (largest != i) { 
		std::swap(arr[i], arr[largest]); 

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest); 
	} 
} 

void parallel_heap_sort_with_lock(int **arr, int size, int threads, int **tmp) 
{ 
  int i;
  omp_set_num_threads(threads);
  
  omp_lock_t lock;
  omp_init_lock(&lock);

  #pragma omp for schedule(static)
	for (i = size / 2 - 1; i >= 0; i--) {
    omp_set_lock(&lock);
		heapify(*arr, size, i); 
    omp_unset_lock(&lock);
  }

  #pragma omp for schedule(static)
	for (i = size - 1; i >= 0; i--) { 
    omp_set_lock(&lock);
		std::swap((*arr)[0], (*arr)[i]); 
		heapify(*arr, i, 0);
    omp_unset_lock(&lock);
	} 

  omp_destroy_lock(&lock);
} 

}// namespace sequencial