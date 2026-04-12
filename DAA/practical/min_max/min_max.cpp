#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

long long comparisons = 0;

bool isGreater(int a, int b) {
    comparisons++;
    return a > b;
}

bool isLess(int a, int b) {
    comparisons++;
    return a < b;
}

// Basic Linear Search 
void getMinMaxLinear(const vector<int>& arr, int& minVal, int& maxVal) {
    comparisons = 0;
    int n = arr.size();
    if (n == 0) return;

    minVal = arr[0];
    maxVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (isGreater(arr[i], maxVal)) maxVal = arr[i];
        else if (isLess(arr[i], minVal)) minVal = arr[i];
    }
}

// Pair Comparison
void getMinMaxPair(const vector<int>& arr, int& minVal, int& maxVal) {
    comparisons = 0;
    int n = arr.size();
    if (n == 0) return;

    int i;
    if (n % 2 == 0) {
        if (isGreater(arr[0], arr[1])) {
            maxVal = arr[0];
            minVal = arr[1];
        } else {
            minVal = arr[0];
            maxVal = arr[1];
        }
        i = 2;
    } else {
        minVal = arr[0];
        maxVal = arr[0];
        i = 1;
    }

    while (i < n - 1) {
        if (isGreater(arr[i], arr[i + 1])) {
            if (isGreater(arr[i], maxVal)) maxVal = arr[i];
            if (isLess(arr[i + 1], minVal)) minVal = arr[i + 1];
        } else {
            if (isGreater(arr[i + 1], maxVal)) maxVal = arr[i + 1];
            if (isLess(arr[i], minVal)) minVal = arr[i];
        }
        i += 2;
    }
}

// Divide and Conquer
struct Pair {
    int min;
    int max;
};

Pair getMinMaxDC_Recursive(const vector<int>& arr, int low, int high) {
    Pair minmax, mml, mmr;
    int mid;

    if (low == high) {
        minmax.max = arr[low];
        minmax.min = arr[low];
        return minmax;
    }

    if (high == low + 1) {
        if (isGreater(arr[low], arr[high])) {
            minmax.max = arr[low];
            minmax.min = arr[high];
        } else {
            minmax.max = arr[high];
            minmax.min = arr[low];
        }
        return minmax;
    }

    mid = (low + high) / 2;
    mml = getMinMaxDC_Recursive(arr, low, mid);
    mmr = getMinMaxDC_Recursive(arr, mid + 1, high);

    if (isLess(mml.min, mmr.min)) minmax.min = mml.min;
    else minmax.min = mmr.min;

    if (isGreater(mml.max, mmr.max)) minmax.max = mml.max;
    else minmax.max = mmr.max;

    return minmax;
}

void getMinMaxDC(const vector<int>& arr, int& minVal, int& maxVal) {
    comparisons = 0;
    Pair p = getMinMaxDC_Recursive(arr, 0, arr.size() - 1);
    minVal = p.min;
    maxVal = p.max;
}

void getMinMaxSTL(const vector<int>& arr, int& minVal, int& maxVal) {
    comparisons = 0;
    if (arr.empty()) return;
    auto result = minmax_element(arr.begin(), arr.end(), [](int a, int b) {
        comparisons++;
        return a < b;
    });
    minVal = *result.first;
    maxVal = *result.second;
}

int main() {
    ifstream inputFile("arrays_dataset.txt");
    
    ofstream outFile("min_max_stats.csv");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open 'arrays_dataset.txt'. Please check if the file exists.\n";
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Error: Could not create 'min_max_stats.csv'.\n";
        return 1;
    }

    outFile << "Function,Array_Size,Comparisons\n";

    string line;
    int lineCount = 0;

    while (getline(inputFile, line)) {
        vector<int> arr;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            try {
                if (!value.empty()) {
                    arr.push_back(stoi(value));
                }
            } catch (...) { continue; }
        }

        if (arr.empty()) continue;

        int minVal, maxVal;
        int n = arr.size();

        getMinMaxLinear(arr, minVal, maxVal);
        outFile << "Linear Search," << n << "," << comparisons << "\n";

        getMinMaxPair(arr, minVal, maxVal);
        outFile << "Pair Comparison," << n << "," << comparisons << "\n";

        // getMinMaxDC(arr, minVal, maxVal);
        // outFile << "Divide & Conquer," << n << "," << comparisons << "\n";

        getMinMaxSTL(arr, minVal, maxVal);
        outFile << "STL minmax_element," << n << "," << comparisons << "\n";

        lineCount++;
        if (lineCount % 10 == 0) {
            cout << "Processed " << lineCount << " arrays..." << endl;
        }
    }

    inputFile.close();
    outFile.close();
    cout << "Done! Results saved to 'min_max_stats.csv'." << endl;

    return 0;
}