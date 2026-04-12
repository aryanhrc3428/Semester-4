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

void printBuckets(const vector<vector<int>> &buckets, int exp) {
    cout << "\n--- Pass for position: " << exp << " (1=Units, 10=Tens, etc.) ---\n";
    for (int i = 0; i < 10; i++) {
        cout << "Bucket " << i << ": [ ";
        if (buckets[i].empty()) {
            cout << ""; 
        } else {
            for (int val : buckets[i]) {
                cout << val << " ";
            }
        }
        cout << "]\n";
    }
}

void radixSort(vector<int> &arr, SortStats &stats) {
    int n = arr.size();
    if (n == 0) return;

    int m = getMax(arr, stats);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        vector<vector<int>> buckets(10);

        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            buckets[digit].push_back(arr[i]);
        }

        printBuckets(buckets, exp);

        int index = 0;
        for (int i = 0; i < 10; i++) {
            for (int val : buckets[i]) {
                arr[index++] = val;
            }
        }
        
        cout << "Array after this pass: ";
        for(int x : arr) cout << x << " ";
        cout << "\n";
    }
}

int main() {     
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Input Array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    SortStats stats;
    
    radixSort(arr, stats);

    cout << "\n-------------------------------\n";
    cout << "Total Comparisons (Finding Max): " << stats.comparisons << "\n";
    
    cout << "Sorted Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}