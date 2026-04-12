#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

struct SortStats {
    long long comparisons = 0;
    long long movements = 0;
    long long merges = 0;
};

void merge(vector<int>& arr, int l, int m, int r, SortStats& stats) {
    stats.merges++;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        stats.movements++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        stats.movements++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        stats.movements++;
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r, SortStats& stats) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, stats);
        mergeSort(arr, m + 1, r, stats);
        merge(arr, l, m, r, stats);
    }
}

int main() {
    ifstream input("arrays_dataset.txt");
    
    ifstream check_empty("comparison.csv");
    bool is_empty = check_empty.peek() == EOF;
    check_empty.close();

    ofstream output("comparison.csv", ios::app);

    if (!input.is_open() || !output.is_open()) {
        cout << "Error opening files.\n";
        return 1;
    }

    if (is_empty) {
        output << "arr_num,arr_size,avg_comparison,avg_passes,avg_shifts,best_case_comparison,worst_case_comparison\n";
    }

    string line;
    int batchCounter = 0;
    int batchNumber = 1;
    int testCase = 1;

    long long sum_comparisons = 0;
    long long sum_movements = 0; 
    long long sum_merges = 0;    
    
    long long min_comparisons = numeric_limits<long long>::max();
    long long max_comparisons = numeric_limits<long long>::min();
    
    int current_arr_size = 0;

    while (getline(input, line)) {
        vector<int> arr;
        string value;
        stringstream ss(line);

        while (getline(ss, value, ',')) {
            try {
                if (!value.empty()) {
                    arr.push_back(stoi(value));
                }
            } catch (...) { continue; }
        }
        
        if (arr.empty()) continue;

        current_arr_size = arr.size();
        SortStats stats;
        
        mergeSort(arr, 0, arr.size() - 1, stats);

        sum_comparisons += stats.comparisons;
        sum_movements   += stats.movements;
        sum_merges      += stats.merges;

        if (stats.comparisons < min_comparisons) min_comparisons = stats.comparisons;
        if (stats.comparisons > max_comparisons) max_comparisons = stats.comparisons;

        batchCounter++;

        cout << "Test Case " << testCase++
             << " | Size: " << current_arr_size
             << " | Comparisons: " << stats.comparisons
             << " | Movements: " << stats.movements
             << " | Merges: " << stats.merges << endl;

        if (batchCounter == 10) {
            double avg_comp = sum_comparisons / 10.0;
            double avg_pass = sum_merges / 10.0;    
            double avg_shft = sum_movements / 10.0; 

            // Write to CSV
            output << batchNumber << "," 
                   << current_arr_size << "," 
                   << avg_comp << "," 
                   << avg_pass << "," 
                   << avg_shft << "," 
                   << min_comparisons << "," 
                   << max_comparisons << "\n"; 

            sum_comparisons = 0;
            sum_movements = 0;
            sum_merges = 0;
            min_comparisons = numeric_limits<long long>::max();
            max_comparisons = numeric_limits<long long>::min();
            batchCounter = 0;
            batchNumber++;
        }
    }

    input.close();
    output.close();
    return 0;
}