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

int getMax(vector<int> &arr, SortStats &stats) {
    int maxVal = arr[0];
    int n = arr.size();
    
    stats.passes++; 
    
    for (int i = 1; i < n; i++) {
        stats.comparisons++;
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

void countSort(vector<int> &arr, SortStats &stats) {
    int n = arr.size();
    if (n == 0) return;

    int maxVal = getMax(arr, stats);

    vector<int> count(maxVal + 1, 0);
    vector<int> output(n);

    stats.passes++;
    for (int i = 0; i < n; i++) count[arr[i]]++;

    stats.passes++;
    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];

    stats.passes++;
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
        stats.shifts++;
    }

    stats.passes++;
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        stats.shifts++;
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
        countSort(arr, stats);
        
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