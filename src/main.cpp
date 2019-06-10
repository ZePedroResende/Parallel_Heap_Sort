#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include "parallel.hpp"
#include "sequencial.hpp"
#include "test.hpp"

using namespace std;

void clearCache(void) {
  vector<int>* clearcache = new vector<int>;
  for (int i = 0; i < 253999999; ++i) clearcache->push_back(i);
  clearcache->clear();
  for (int i = 0; i < 253999999; ++i) clearcache->push_back(i - 1);
  clearcache->clear();
  for (int i = 0; i < 253999999; ++i) clearcache->push_back(i + 1);
  clearcache->clear();
  for (int i = 503999999; i > 0; i--) clearcache->push_back(i);
  delete clearcache;
}

vector<int>& readArray(char* file) {
  vector<int>* mas;
  ifstream* ifs;

  try {
    ifs = new ifstream(file, ios_base::in);
  } catch (exception e) {
    cout << "Failed to read file. " << e.what() << endl;
    exit(-1);
  }

  try {
    mas = new vector<int>();
  } catch (exception e) {
    cout << "Array memory allocation gone terribly wrong." << endl;
    exit(-2);
  }

  int buf;

  while (!ifs->eof()) {
    *ifs >> buf;
    mas->push_back(buf);
  }

  ifs->close();
  delete ifs;
  return *mas;
}

int main(int argc, char* argv[]) {
  // awesomeGenerator("ints_10kk.txt", 10000000);
  vector<int> arr;
  vector<int> arr_par;
  /*
  if (argc == 2)
    arr = readArray(&argv[1]);
  else
    */
  arr = readArray("ints_3.0kk.txt");
  int size = arr.size();

  arr_par = arr;

  float before, after;
  before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  test::heap_sort(arr);
  after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  auto posl = after - before;
  cout << "array size " << size << " time: " << posl << endl;
  
  // int* arr1 = arr_par.data();
  // int* arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, size, 2, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // auto par = after - before;
  // cout << " 2 array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // auto equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 2, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 2 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 4, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "4 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 4, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 4 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[arr.size()];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 8, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "8 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 8, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 8 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[arr.size()];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 16, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "16 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 16, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 16 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[arr.size()];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 32, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "32 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 32, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 32 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[arr.size()];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 64, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "64 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 64, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 64 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[arr.size()];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort(&arr1, arr.size(), 128, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << "128 array size" << arr.size() << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  // arr1 = arr_par.data();
  // arr2 = new int[size];

  // before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // sequencial::parallel_heap_sort_with_lock(&arr1, size, 128, &arr2);
  // after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  // par = after - before;
  // cout << " 128 with locks | array size" << size << " time: " << par << endl;
  // cout << "percentagem : " << 100 - (par / posl * 100) << "%" << endl;

  // equal = true;
  // for (auto i = 0; i < arr.size(); ++i) {
  //   equal = equal && (arr.at(i) == arr1[i]);
  //   if (!equal) break;
  // }
  
  // equal ? cout << "Equal !" << endl : cout << "Different :(" << endl;

  arr.clear();
  arr_par.clear();
  return 0;
}

