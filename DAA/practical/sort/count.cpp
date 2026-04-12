#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct SortStats {
    long long comparisons = 0;
};

int getMax(vector<int> &arr, SortStats &stats) {
    if (arr.empty()) return 0;
    
    int maxVal = arr[0];
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        stats.comparisons++;
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

void countSort(vector<int> &arr, SortStats &stats, vector<int> *count_out = nullptr) {
    int n = arr.size();
    if (n == 0) return;

    int maxVal = getMax(arr, stats);

    vector<int> count(maxVal + 1, 0);
    vector<int> output(n);

    for (int i = 0; i < n; i++) count[arr[i]]++;

    if (count_out) *count_out = count; 

    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

int main() {
    vector<int> arr = {10, 45, 75, 90, 80, 24, 2, 66};

    cout << "Input Array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";

    SortStats stats;
    vector<int> freq;
    
    countSort(arr, stats, &freq);
    
    cout << "Count Array (Frequency): [";
    for (size_t i = 0; i < freq.size(); ++i) {
        if (i) cout << ", ";
        cout << freq[i];
    }
    cout << "]\n";
    cout << "Comparisons: " << stats.comparisons << "\n";
    
    cout << "Sorted Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}