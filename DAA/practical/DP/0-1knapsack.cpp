#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

struct Item {
    int id;
    int value;
    int weight;
    double ratio;
};

// 0-1 Knapsack - Recursive (Naive)
int knapsackRecursive(int n, int capacity, const vector<Item>& items) {
    if (n == 0 || capacity == 0) {
        return 0;
    }
    
    if (items[n].weight > capacity) {
        return knapsackRecursive(n - 1, capacity, items);
    }
    
    int include = items[n].value + knapsackRecursive(n - 1, capacity - items[n].weight, items);
    int exclude = knapsackRecursive(n - 1, capacity, items);
    
    return max(include, exclude);
}

// 0-1 Knapsack - Memoized DP
int knapsackMemoized(int n, int capacity, const vector<Item>& items, vector<vector<int>>& memo) {
    if (n == 0 || capacity == 0) {
        return 0;
    }
    
    if (memo[n][capacity] != -1) {
        return memo[n][capacity];
    }
    
    if (items[n].weight > capacity) {
        memo[n][capacity] = knapsackMemoized(n - 1, capacity, items, memo);
    } else {
        int include = items[n].value + knapsackMemoized(n - 1, capacity - items[n].weight, items, memo);
        int exclude = knapsackMemoized(n - 1, capacity, items, memo);
        memo[n][capacity] = max(include, exclude);
    }
    
    return memo[n][capacity];
}

// 0-1 Knapsack - Iterative DP (Bottom-up)
int knapsackIterative(int n, int capacity, const vector<Item>& items) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(dp[i - 1][w], items[i].value + dp[i - 1][w - items[i].weight]);
            }
        }
    }
    
    return dp[n][capacity];
}

// Reconstruct solution for memoized approach
void reconstructSolution(int n, int capacity, const vector<Item>& items, const vector<vector<int>>& memo, vector<int>& selected) {
    int i = n, w = capacity;
    while (i > 0 && w > 0) {
        if (memo[i][w] != memo[i - 1][w]) {
            selected.push_back(i);
            w = w - items[i].weight;
        }
        i--;
    }
    reverse(selected.begin(), selected.end());
}

// Reconstruct solution for iterative DP
void reconstructSolutionIterative(int n, int capacity, const vector<Item>& items, vector<vector<int>>& dp, vector<int>& selected) {
    int i = n, w = capacity;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w = w - items[i].weight;
        }
        i--;
    }
    reverse(selected.begin(), selected.end());
}

int main() {
    int n;
    int capacity;

    cout << "=== 0-1 Knapsack Problem ===\n";
    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> capacity;

    vector<Item> items(n + 1);
    items[0] = {0, 0, 0, 0};

    cout << "\nEnter the Value and Weight for each item:\n";
    for (int i = 1; i <= n; i++) {
        items[i].id = i;
        cout << "Item " << i << " Value: ";
        cin >> items[i].value;
        cout << "Item " << i << " Weight: ";
        cin >> items[i].weight;
        
        if (items[i].weight > 0) {
            items[i].ratio = (double)items[i].value / items[i].weight;
        } else {
            items[i].ratio = 0;
        }
    }

    cout << "\n[1] Recursive Approach:\n";
    auto start_time = high_resolution_clock::now();
    int recursiveResult = knapsackRecursive(n, capacity, items);
    auto end_time = high_resolution_clock::now();
    auto duration_recursive = duration_cast<nanoseconds>(end_time - start_time).count();
    
    cout << "    Result: " << recursiveResult << "\n";
    cout << "    Time taken: " << duration_recursive << " ns\n";
    
    vector<vector<int>> memo(n + 1, vector<int>(capacity + 1, -1));
    knapsackMemoized(n, capacity, items, memo);
    vector<int> selected;
    reconstructSolution(n, capacity, items, memo, selected);
    cout << "    Selected Items: ";
    for (int idx : selected) {
        cout << idx << " ";
    }
    cout << "\n";

    cout << "\n[2] Memoized DP Approach:\n";
    vector<vector<int>> memoTable(n + 1, vector<int>(capacity + 1, -1));
    start_time = high_resolution_clock::now();
    int memoizedResult = knapsackMemoized(n, capacity, items, memoTable);
    end_time = high_resolution_clock::now();
    auto duration_memoized = duration_cast<nanoseconds>(end_time - start_time).count();
    
    cout << "    Result: " << memoizedResult << "\n";
    cout << "    Time taken: " << duration_memoized << " ns\n";
    
    vector<int> selectedMemo;
    reconstructSolution(n, capacity, items, memoTable, selectedMemo);
    cout << "    Selected Items: ";
    for (int idx : selectedMemo) {
        cout << idx << " ";
    }
    cout << "\n";

    cout << "\n[3] Iterative DP Approach:\n";
    start_time = high_resolution_clock::now();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    int iterativeResult = knapsackIterative(n, capacity, items);
    end_time = high_resolution_clock::now();
    auto duration_iterative = duration_cast<nanoseconds>(end_time - start_time).count();
    
    cout << "    Result: " << iterativeResult << "\n";
    cout << "    Time taken: " << duration_iterative << " ns\n";
    
    vector<vector<int>> dpRecon(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i].weight > w) {
                dpRecon[i][w] = dpRecon[i - 1][w];
            } else {
                dpRecon[i][w] = max(dpRecon[i - 1][w], items[i].value + dpRecon[i - 1][w - items[i].weight]);
            }
        }
    }
    vector<int> selectedIter;
    reconstructSolutionIterative(n, capacity, items, dpRecon, selectedIter);
    cout << "    Selected Items: ";
    for (int idx : selectedIter) {
        cout << idx << " ";
    }
    cout << "\n";

    cout << "----------------------------------------------------\n";
    cout << "Optimal 0-1 Knapsack Result: " << iterativeResult << "\n";
    cout << "====================================================\n\n";

    return 0;
}