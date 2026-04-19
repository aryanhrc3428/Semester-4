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
};

bool compareJobs(const Job& a, const Job& b) {
    return a.finish < b.finish;
}

pair<int, vector<int>> greedyIntervalScheduling(const vector<Job>& jobs) {
    int n = jobs.size() - 1;
    vector<int> selected;
    
    if (n == 0) return {0, selected};
    
    int count = 1;
    int lastFinish = jobs[1].finish;
    selected.push_back(1);
    
    for (int i = 2; i <= n; i++) {
        if (jobs[i].start >= lastFinish) {
            count++;
            lastFinish = jobs[i].finish;
            selected.push_back(i);
        }
    }
    return {count, selected};
}

int main() {
    int n;
    cout << "=== Greedy Interval Scheduling ===\n";
    cout << "Enter the number of jobs/intervals: ";
    cin >> n;

    vector<Job> jobs(n + 1);
    jobs[0] = {0, 0, 0};

    cout << "\nEnter " << n << " jobs in format (Start Finish):\n";
    for (int i = 1; i <= n; i++) {
        jobs[i].id = i;
        cin >> jobs[i].start >> jobs[i].finish;
    }

    sort(jobs.begin() + 1, jobs.end(), compareJobs);

    cout << "\n------------------------------------------------\n";
    
    auto start_time = high_resolution_clock::now();
    auto greedyResult = greedyIntervalScheduling(jobs);
    auto end_time = high_resolution_clock::now();
    auto duration_greedy = duration_cast<nanoseconds>(end_time - start_time).count();
    
    cout << "Greedy Interval Scheduling Result: " << greedyResult.first << " jobs\n";
    cout << "Time taken: " << duration_greedy << " ns\n";
    cout << "Selected Jobs:\n";
    for (int idx : greedyResult.second) {
        cout << "  -> Job ID " << jobs[idx].id 
             << " [Start: " << jobs[idx].start 
             << ", Finish: " << jobs[idx].finish << "]\n";
    }
    cout << "Total Selected: " << greedyResult.first << "\n";

    cout << "------------------------------------------------\n\n";

    return 0;
}
