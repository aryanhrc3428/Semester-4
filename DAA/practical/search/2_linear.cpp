#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

long long comparisons = 0;

int linearSearch(const vector<int>& arr, int target) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    ifstream input("lin_dataset.txt");
    
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
        int target = -999999; 
        linearSearch(arr, target);

        output << "Linear Search," << arr.size() << "," << comparisons << "\n";
    }

    input.close();
    output.close();
    cout << "Linear Search processed. Data appended to 'search_comparisons.csv'" << endl;
    return 0;
}