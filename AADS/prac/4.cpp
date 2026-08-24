/* return index of element that sums up to target */

#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {}; 
}

int main() {
    vector<int> nums = {2,7,12,15,1,4};
    int target = 9;
    vector<int> res = twoSum(nums, target);
    
    if(res[0] == res[1]) cout << "No answer found" << endl;
    else cout << "Target found: " << res[0] << " and " << res[1] << endl;
    return 0;
}