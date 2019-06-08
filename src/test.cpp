#include "test.hpp"
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
namespace test {

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

void shift_down(vector<int>& a, int i, int j) {
  auto done = false;
  int maxChild;
  while ((i * 2 + 1 < j) && !done) {
    if (i * 2 + 1 == j - 1)
      maxChild = i * 2 + 1;
    else if (a.at(i * 2 + 1) > a.at(i * 2 + 2))
      maxChild = i * 2 + 1;
    else
      maxChild = i * 2 + 2;

    if (a.at(i) < a.at(maxChild)) {
      swap(a.at(i), a.at(maxChild));
      i = maxChild;
    } else
      done = true;
  }
}

void heap_sort(vector<int>& a) {
  int i;
  auto size = a.size();
  for (i = size / 2 - 1; i >= 0; --i) shift_down(a, i, size);

  for (i = size - 1; i >= 1; --i) {
    swap(a.at(0), a.at(i));
    shift_down(a, 0, i);
  }
}

void mergeVectors(vector<int>* a, vector<int>* b, vector<int>* r) {
  auto i = 0;
  auto j = 0;
  auto index = 0;
  auto n = a->size();
  auto m = b->size();

  while (i < n && j < m) {
    if (a->at(i) < b->at(j)) {
      r->at(index) = a->at(i);
      ++i;
    } else {
      r->at(index) = b->at(j);
      ++j;
    }
    ++index;
  }

  while (i < n) {
    r->at(index) = a->at(i);
    ++index;
    ++i;
  }

  while (j < m) {
    r->at(index) = b->at(j);
    ++index;
    ++j;
  }
}

void heap_sort_parallel(vector<int>& a) {
  auto numOfThreads = omp_get_max_threads();
  cout << "Sorting in " << numOfThreads << " threads" << endl;
  vector<vector<int>*> subMas;
  int elementsPerSubMassive =
      static_cast<int>(ceil(static_cast<float>(a.size()) / numOfThreads));
  auto it = a.begin();
  for (auto j = 0; j < numOfThreads; ++j) {
    subMas.push_back(new vector<int>());
    for (auto z = 0; z < elementsPerSubMassive; ++z) {
      if (*it) {
        subMas.at(j)->push_back(*it);
        ++it;
      } else
        break;
    }
  }

  a.clear();
  a.shrink_to_fit();

#pragma omp parallel num_threads(numOfThreads) shared(subMas)
  {
    int i;
    auto threadNumber = omp_get_thread_num();
    auto size = subMas.at(threadNumber)->size();

    for (i = size / 2 - 1; i >= 0; --i)
      shift_down(*subMas.at(threadNumber), i, size);

    for (i = size - 1; i >= 1; --i) {
      swap(subMas.at(threadNumber)->at(0), subMas.at(threadNumber)->at(i));
      shift_down(*subMas.at(threadNumber), 0, i);
    }
  }

  auto* m1 = new vector<int>(subMas.at(0)->size() + subMas.at(1)->size());
  auto* m2 = new vector<int>(subMas.at(2)->size() + subMas.at(3)->size());
  auto* m3 = new vector<int>(subMas.at(0)->size() + subMas.at(1)->size() +
                             subMas.at(2)->size() + subMas.at(3)->size());

  mergeVectors(subMas.at(0), subMas.at(1), m1);
  mergeVectors(subMas.at(2), subMas.at(3), m2);
  mergeVectors(m1, m2, m3);
  a = *m3;
  subMas.clear();
  subMas.shrink_to_fit();
  delete m1;
  delete m2;
  delete m3;
}

void awesomeGenerator(char* file, int num) {
  ofstream* ofs;
  try {
    ofs = new ofstream(file, ios_base::out | ios_base::trunc);
  } catch (exception e) {
    cout << "Failed to write file. " << e.what() << endl;
    exit(-1);
  }
  auto before = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  auto i = 0;

  for (i = 0; i < num; ++i) *ofs << rand() % 1000000 + 1 << endl;

  auto after = static_cast<float>(clock()) / CLOCKS_PER_SEC;
  cout << "������������ ����� ���� �� " << num << " ����� �� " << after - before
       << endl;
  ofs->close();
  delete ofs;
}

}  // namespace test

