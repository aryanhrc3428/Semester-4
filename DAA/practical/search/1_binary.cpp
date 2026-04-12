#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

long long comparisons = 0;

int binarySearch(const vector<int>& arr, int target) {
    comparisons = 0;
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    ifstream input("bin_dataset.txt");
    
    ifstream check_empty("search_comparisons.csv");
    bool is_empty = check_empty.peek() == EOF;
    check_empty.close();

    ofstream output("search_comparisons.csv", ios::app);

    if (!input.is_open() || !output.is_open()) {
        cout << "Error opening files.\n";
        return 1;
    }

    if (is_empty) {
        output << "search algo,array_size,no._of_comparisons\n";
    }

    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        vector<int> arr;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            try {
                if (!value.empty()) arr.push_back(stoi(value));
            } catch (...) { continue; }
        }

        if (arr.empty()) continue;
        sort(arr.begin(), arr.end());
        int target = -999999; 

        binarySearch(arr, target);

        output << "Binary Search," << arr.size() << "," << comparisons << "\n";
    }

    input.close();
    output.close();
    cout << "Binary Search processed. Data appended to 'search_comparisons.csv'" << endl;
    return 0;
}