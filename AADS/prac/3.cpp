#include <bits/stdc++.h>
using namespace std; 

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    if (k == 0) return;
    if (k > nums.size() - 1) k = k % (nums.size() - 1);
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

int main () {
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    rotate(nums, k);
    
    cout << "Rotated list: [ ";
    for (int it : nums) {
        cout << it << " ";
    } cout << "]" << endl;
    
    return 0;
}