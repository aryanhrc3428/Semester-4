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
    long long shifts = 0;
    long long passes = 0;
};

int partition(vector<int> &arr, int low, int high, SortStats &stats) {
    stats.passes++;
    
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats.comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            stats.shifts++;
        }
    }
    swap(arr[i + 1], arr[high]);
    stats.shifts++;
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high, SortStats &stats) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, stats);
        quickSort(arr, low, pivotIndex - 1, stats);
        quickSort(arr, pivotIndex + 1, high, stats);
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
    int testCase = 1;
    int batchCounter = 0;
    int batchNumber = 1;

    long long sum_comparisons = 0;
    long long sum_shifts = 0;
    long long sum_passes = 0;

    long long min_comparisons = numeric_limits<long long>::max();
    long long max_comparisons = numeric_limits<long long>::min();

    while (getline(input, line)) {
        vector<int> arr;
        string value;
        stringstream ss(line);

        while (getline(ss, value, ',')) {
            try {
                if (!value.empty()) {
                    arr.push_back(stoi(value));
                }
            } catch (...) {
                continue;
            }
        }

        if (arr.empty()) continue;

        SortStats stats;
        quickSort(arr, 0, arr.size() - 1, stats);
        
        sum_comparisons += stats.comparisons;
        sum_shifts += stats.shifts;
        sum_passes += stats.passes;

        if (stats.comparisons < min_comparisons) min_comparisons = stats.comparisons;
        if (stats.comparisons > max_comparisons) max_comparisons = stats.comparisons;

        batchCounter++;

        cout << "Test Case " << testCase++
             << " | Size: " << arr.size()
             << " | Comparisons: " << stats.comparisons
             << " | Shifts: " << stats.shifts
             << " | Passes: " << stats.passes << endl;

        if (batchCounter == 10) {
            double avg_comp = sum_comparisons / 10.0;
            double avg_pass = sum_passes / 10.0;
            double avg_shft = sum_shifts / 10.0;

            output << batchNumber << "," 
                   << arr.size() << "," 
                   << avg_comp << "," 
                   << avg_pass << "," 
                   << avg_shft << "," 
                   << min_comparisons << "," 
                   << max_comparisons << "\n";
            
            sum_comparisons = 0;
            sum_shifts = 0;
            sum_passes = 0;
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