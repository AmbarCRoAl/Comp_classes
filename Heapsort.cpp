#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <class elemType>
void heapify(vector<elemType>& list, int low, int high) {
  int largeIndex;
  elemType temp = list[low];
  largeIndex = 2 * low + 1;

  while (largeIndex <= high) {
    if (largeIndex < high) {
      if (list[largeIndex] < list[largeIndex + 1]) 
        largeIndex = largeIndex + 1;
    }
    if (temp > list[largeIndex])
      break;
    else {
      list[low] = list[largeIndex];
      low = largeIndex;
      largeIndex = 2 * low + 1;
    }
  }

  list[low] = temp;
}

template <class elemType>
void buildHeap(vector<elemType>& list) {
  for (int index = list.size() / 2 - 1; index >= 0; index--) {
    heapify(list, index, list.size() - 1);
  }
}

template <class elemType>
void heapSort(vector<elemType>& list) {
  elemType temp;
  buildHeap(list);

  for (int lastOutOfOrder = list.size() - 1; lastOutOfOrder >= 0;
       lastOutOfOrder--) {
    temp = list[lastOutOfOrder];
    list[lastOutOfOrder] = list[0];
    list[0] = temp;
    heapify(list, 0, lastOutOfOrder - 1);
  }
}

void normalSort(vector<int>& list) {
  int k, j;
  for (int i = 1; i < list.size(); i++) {
    k = list[i];
    j = i - 1;

    while (j >= 0 && list[j] > k) {
      list[j + 1] = list[j];
      j = j - 1;
    }
    list[j + 1] = k;
  }
}

int main() {
  random_device rd;
  default_random_engine engine(rd());
  uniform_int_distribution<int> gen_numberRanged(1, 1000);

  int counter = 12;
  vector<int> nums;
  cout << "\n\t\tArreglo Original";
  for (int i = 0; i < gen_numberRanged(engine) * 1000; i++) {
    nums.push_back(gen_numberRanged(engine));
    if (counter == 12) {
      cout << "\n\t\t" << nums[i];
      counter = 0;
    }
    else 
      cout<< "\t" << nums[i];
    counter++;
  }

  vector<int> copy;
  copy.assign(nums.begin(), nums.end());

  auto start = std::chrono::steady_clock::now();
  heapSort(nums);
  auto end = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "\n\n\t\tTiempo HeapSort: " << elapsed.count() << " micro segundos";

  auto start2 = std::chrono::steady_clock::now();
  normalSort(copy);
  auto end2 = std::chrono::steady_clock::now();
  auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
  cout << "\n\t\tTiempo InsertionSort: " << elapsed2.count()
       << " micro segundos";
  cout << "\n\t\tPresione enter para ver el arreglo resultante";
  cin.get();
  cout << "\n\t\tArreglo Ordenado";
  counter = 12;
  for (int i = 0; i < nums.size() - 1; i++) {
    if (counter == 12) {
      cout << "\n\t\t" << nums[i];
      counter = 0;
    }
    else {
      cout<< "\t" << nums[i];
      counter++;
    }
  }
  cin.get();

  return 0;
}
