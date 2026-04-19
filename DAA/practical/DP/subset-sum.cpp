#include <iostream>
#include <vector>
using namespace std;

bool subsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
 
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            // Don't include current element
            dp[i][j] = dp[i-1][j];
            
            // Include current element if it doesn't exceed sum j
            if (j >= arr[i-1]) {
                dp[i][j] = dp[i][j] || dp[i-1][j - arr[i-1]];
            }
        }
    }
    
    return dp[n][target];
}

// Space optimized version using 1D array
bool subsetSumOptimized(vector<int>& arr, int target) {
    int n = arr.size();
    vector<bool> dp(target + 1, false);
    dp[0] = true; // sum 0 is always achievable
    
    for (int i = 0; i < n; i++) {
        // Traverse backwards to avoid using updated values
        for (int j = target; j >= arr[i]; j--) {
            dp[j] = dp[j] || dp[j - arr[i]];
        }
    }
    
    return dp[target];
}

// Function to print the subset that sums to target
bool subsetSumWithPath(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= arr[i-1]) {
                dp[i][j] = dp[i][j] || dp[i-1][j - arr[i-1]];
            }
        }
    }
    
    if (!dp[n][target]) {
        return false;
    }
    
    vector<int> subset;
    int i = n, j = target;
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i-1][j]) {
            subset.push_back(arr[i-1]);
            j -= arr[i-1];
        }
        i--;
    }
    
    cout << "Subset: { ";
    for (int k = subset.size() - 1; k >= 0; k--) {
        cout << subset[k];
        if (k > 0) cout << ", ";
    }
    cout << " }" << endl;
    
    return true;
}

int main() {
    int n, target;
    
    cout << "=== Subset Sum Problem (Dynamic Programming) ===" << endl << endl;
    
    cout << "Enter the number of elements in the set: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Error: Number of elements must be positive!" << endl;
        return 1;
    }
    
    vector<int> arr(n);
    cout << "Enter " << n << " non-negative integers:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Element " << (i + 1) << ": ";
        cin >> arr[i];
        if (arr[i] < 0) {
            cout << "Error: Negative numbers not allowed!" << endl;
            return 1;
        }
    }
    
    cout << "Enter the target sum: ";
    cin >> target;
    
    if (target < 0) {
        cout << "Error: Target sum must be non-negative!" << endl;
        return 1;
    }
    
    cout << endl << "========================================" << endl;
    cout << "Set: { ";
    for (int x : arr) cout << x << " ";
    cout << "}" << endl;
    cout << "Target Sum: " << target << endl;
    cout << "========================================" << endl << endl;
    
    cout << "Using 2D DP approach:" << endl;
    if (subsetSum(arr, target)) {
        cout << "✓ Subset with sum " << target << " exists!" << endl;
        subsetSumWithPath(arr, target);
    } else {
        cout << "✗ No subset with sum " << target << " exists." << endl;
    }
    
    cout << endl;
    
    cout << "Using space optimized (1D) approach:" << endl;
    if (subsetSumOptimized(arr, target)) {
        cout << "✓ Subset with sum " << target << " exists!" << endl;
    } else {
        cout << "✗ No subset with sum " << target << " exists." << endl;
    }
    
    return 0;
}