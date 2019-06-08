#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

namespace test {
void heap_sort(vector<int>& a);
void heap_sort_parallel(vector<int>& a);
}  // namespace test
