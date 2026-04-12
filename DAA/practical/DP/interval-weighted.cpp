#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Job {
    int id;       
    int start;
    int finish;
    int weight;
};

bool compareJobs(const Job& a, const Job& b) {
    return a.finish < b.finish;
}

int findCompatible(const vector<Job>& jobs, int i) {
    int low = 1, high = i - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (jobs[mid].finish <= jobs[i].start) {
            if (jobs[mid + 1].finish <= jobs[i].start) {
                low = mid + 1;
            } else {
                return mid;
            }
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

pair<long long, vector<int>> greedyApproach(const vector<Job>& jobs) {
    int n = jobs.size() - 1;
    vector<int> selected;
    
    if (n == 0) return {0, selected};
    
    long long totalWeight = jobs[1].weight;
    int lastSelected = 1;
    selected.push_back(1);
    
    for (int i = 2; i <= n; i++) {
        if (jobs[i].start >= jobs[lastSelected].finish) {
            totalWeight += jobs[i].weight;
            lastSelected = i;
            selected.push_back(i);
        }
    }
    return {totalWeight, selected};
}

long long recursiveComputeOpt(int j, const vector<Job>& jobs, const vector<int>& p) {
    if (j == 0) {
        return 0;
    }
    long long include_j = jobs[j].weight + recursiveComputeOpt(p[j], jobs, p);
    long long exclude_j = recursiveComputeOpt(j - 1, jobs, p);
    
    return max(include_j, exclude_j);
}

long long memoizedComputeOpt(int j, const vector<Job>& jobs, const vector<int>& p, vector<long long>& M) {
    if (j == 0) {
        return 0;
    }
    if (M[j] != -1) {
        return M[j];
    }
    
    long long include_j = jobs[j].weight + memoizedComputeOpt(p[j], jobs, p, M);
    long long exclude_j = memoizedComputeOpt(j - 1, jobs, p, M);
    
    M[j] = max(include_j, exclude_j);
    return M[j];
}

void findSolution(int j, const vector<Job>& jobs, const vector<int>& p, const vector<long long>& M) {
    if (j == 0) {
        return;
    }
    if (jobs[j].weight + M[p[j]] >= M[j - 1]) {
        findSolution(p[j], jobs, p, M);
        cout << "  -> Job ID " << jobs[j].id 
             << " [Start: " << jobs[j].start 
             << ", Finish: " << jobs[j].finish 
             << ", Weight: " << jobs[j].weight << "]\n";
    } else {
        findSolution(j - 1, jobs, p, M);
    }
}

vector<int> reconstructSolution(int j, const vector<Job>& jobs, const vector<int>& p, const vector<long long>& M) {
    vector<int> solution;
    if (j == 0) {
        return solution;
    }
    if (jobs[j].weight + M[p[j]] >= M[j - 1]) {
        solution = reconstructSolution(p[j], jobs, p, M);
        solution.push_back(j);
    } else {
        solution = reconstructSolution(j - 1, jobs, p, M);
    }
    return solution;
}

int main() {
    int n;
    cout << "=== Weighted Interval Scheduling ===\n";
    cout << "Enter the number of jobs/intervals: ";
    cin >> n;

    vector<Job> jobs(n + 1);
    jobs[0] = {0, 0, 0, 0};

    cout << "\nEnter " << n << " jobs in format (Start Finish Weight):\n";
    for (int i = 1; i <= n; i++) {
        jobs[i].id = i;
        cin >> jobs[i].start >> jobs[i].finish >> jobs[i].weight;
    }

    sort(jobs.begin() + 1, jobs.end(), compareJobs);

    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        p[i] = findCompatible(jobs, i);
    }

    cout << "\n------------------------------------------------\n";
    
    auto start_time = high_resolution_clock::now();
    auto greedyResult = greedyApproach(jobs);
    auto end_time = high_resolution_clock::now();
    auto duration_greedy = duration_cast<nanoseconds>(end_time - start_time).count();
    
    cout << "[1] Greedy Approach Result: " << greedyResult.first << "\n";
    cout << "    Time taken: " << duration_greedy << " ns\n";
    cout << "    Selected Jobs:\n";
    for (int idx : greedyResult.second) {
        cout << "      -> Job ID " << jobs[idx].id 
             << " [Start: " << jobs[idx].start 
             << ", Finish: " << jobs[idx].finish 
             << ", Weight: " << jobs[idx].weight << "]\n";
    }
    cout << "    Total Weight: " << greedyResult.first << "\n";

    long long recursiveAns = 0;
    vector<int> recursiveSolution;
    auto duration_recursive = 0LL;
    if (n > 35) {
        cout << "\n[2] Recursive Approach Skipped (n is too large, it would take exponentially long!)\n";
    } else {
        start_time = high_resolution_clock::now();
        recursiveAns = recursiveComputeOpt(n, jobs, p);
        end_time = high_resolution_clock::now();
        duration_recursive = duration_cast<nanoseconds>(end_time - start_time).count();
        
        // Reconstruct solution for recursive approach
        vector<long long> M_temp(n + 1, -1);
        M_temp[0] = 0;
        memoizedComputeOpt(n, jobs, p, M_temp);
        recursiveSolution = reconstructSolution(n, jobs, p, M_temp);
        
        cout << "\n[2] Naive Recursive Result: " << recursiveAns << "\n";
        cout << "    Time taken: " << duration_recursive << " ns\n";
        cout << "    Selected Jobs:\n";
        for (int idx : recursiveSolution) {
            cout << "      -> Job ID " << jobs[idx].id 
                 << " [Start: " << jobs[idx].start 
                 << ", Finish: " << jobs[idx].finish 
                 << ", Weight: " << jobs[idx].weight << "]\n";
        }
        cout << "    Total Weight: " << recursiveAns << "\n";
    }

    vector<long long> M(n + 1, -1);
    M[0] = 0; 
    
    start_time = high_resolution_clock::now();
    long long memoizedAns = memoizedComputeOpt(n, jobs, p, M);
    end_time = high_resolution_clock::now();
    auto duration_memoized = duration_cast<nanoseconds>(end_time - start_time).count();
    
    vector<int> memoizedSolution = reconstructSolution(n, jobs, p, M);
    
    cout << "\n[3] Memoized DP Result:     " << memoizedAns << "\n";
    cout << "    Time taken: " << duration_memoized << " ns\n";
    cout << "    Selected Jobs:\n";
    for (int idx : memoizedSolution) {
        cout << "      -> Job ID " << jobs[idx].id 
             << " [Start: " << jobs[idx].start 
             << ", Finish: " << jobs[idx].finish 
             << ", Weight: " << jobs[idx].weight << "]\n";
    }
    cout << "    Total Weight: " << memoizedAns << "\n";

    cout << "------------------------------------------------\n\n";

    return 0;
}