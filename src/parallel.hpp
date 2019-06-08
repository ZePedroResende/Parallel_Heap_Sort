#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <omp.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

int omp_sort(int **arr, int size, int **tmp);
void DHsort(int **arr, int size, int threads, int **tmp);

#endif
