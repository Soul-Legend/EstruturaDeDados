#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Implementação do Quicksort
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quicksort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Implementação do Heapsort
template <typename T>
void heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapsort(vector<T>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<vector<int>> datasets;
    datasets.push_back(vector<int>(1000));
    datasets.push_back(vector<int>(5000));
    datasets.push_back(vector<int>(10000));
    datasets.push_back(vector<int>(50000));
    datasets.push_back(vector<int>(100000));

    for (auto& dataset : datasets) {
        generate(dataset.begin(), dataset.end(), rand);
    }

    for (const auto& dataset : datasets) {
        vector<int> data_quicksort = dataset;
        vector<int> data_heapsort = dataset;

        clock_t start_time = clock();
        quicksort(data_quicksort, 0, data_quicksort.size() - 1);
        clock_t end_time = clock();
        cout << "Quicksort: " << dataset.size() << " elements, Time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";

        start_time = clock();
        heapsort(data_heapsort);
        end_time = clock();
        cout << "Heapsort: " << dataset.size() << " elements, Time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n";
    }

    return 0;
}
