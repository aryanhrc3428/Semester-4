// 1000 arrays, elements from 1 - 1000, array size from 10 - 1000, for each array: 8 random (suffled). 1 ascending, 1 descending

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// random integer in range [l, r]
int randomInt(int l, int r) {
    return l + rand() % (r - l + 1);
}

// Write a single array to file
void writeArray(ofstream &out, const vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        out << arr[i];
        if (i != arr.size() - 1)
            out << ",";
    }
    out << "\n";
}

int main() {
    srand(time(0));

    const int TOTAL_UNIQUE_ARRAYS = 100;
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 1000;
    const int MIN_VAL = 1;
    const int MAX_VAL = 1000;

    ofstream file("arrays_dataset.txt");

    if (!file.is_open()) {
        cout << "Error opening file\n";
        return 1;
    }

    for (int i = 0; i < TOTAL_UNIQUE_ARRAYS; i++) {

        // Generate base array
        int size = randomInt(MIN_SIZE, MAX_SIZE);
        vector<int> base(size);

        for (int j = 0; j < size; j++) {
            base[j] = randomInt(MIN_VAL, MAX_VAL);
        }

        // 8 shuffled versions
        for (int k = 0; k < 8; k++) {
            vector<int> shuffled = base;
            random_shuffle(shuffled.begin(), shuffled.end());
            writeArray(file, shuffled);
        }

        // Ascending order
        vector<int> ascending = base;
        sort(ascending.begin(), ascending.end());
        writeArray(file, ascending);

        // Descending order
        vector<int> descending = ascending;
        reverse(descending.begin(), descending.end());
        writeArray(file, descending);
    }

    file.close();
    cout << "Dataset generated successfully.\n";

    return 0;
}
