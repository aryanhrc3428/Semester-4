#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int id;
    double value;
    double weight;
    double ratio; 
};

bool cmpMinWeight(const Item& a, const Item& b) {
    return a.weight < b.weight;
}

bool cmpMaxValue(const Item& a, const Item& b) {
    return a.value > b.value;
}

bool cmpMaxRatio(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double runKnapsackStrategy(vector<Item> items, double capacity, const string& strategyName, bool (*cmp)(const Item&, const Item&)) {
    sort(items.begin(), items.end(), cmp);

    cout << "\n--- Strategy: " << strategyName << " ---\n";
    cout << "Sorted Array (ID | Value | Weight | Ratio):\n";
    for (const auto& item : items) {
        cout << "Item " << item.id << " | Val: " << setw(5) << item.value 
             << " | Wt: " << setw(5) << item.weight 
             << " | Ratio: " << fixed << setprecision(2) << item.ratio << "\n";
    }

    double totalProfit = 0.0;
    double currentWeight = 0.0;

    cout << "\nActions:\n";
    for (const auto& item : items) {
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalProfit += item.value;
            cout << "Took all of Item " << item.id << " (Added Value: " << item.value << ")\n";
        } else {
            double remainingCapacity = capacity - currentWeight;
            double fraction = remainingCapacity / item.weight;
            double fractionalValue = item.value * fraction;
            
            totalProfit += fractionalValue;
            currentWeight += remainingCapacity;
            
            cout << "Took " << fixed << setprecision(2) << (fraction * 100) 
                 << "% of Item " << item.id << " (Added Value: " << fractionalValue << ")\n";
            break; 
        }
    }
    
    cout << "-> Total Profit for this strategy: " << fixed << setprecision(2) << totalProfit << "\n";
    return totalProfit;
}

int main() {
    int n;
    double capacity;

    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> capacity;

    vector<Item> items(n);
    cout << "\nEnter the Value and Weight for each item:\n";
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        cout << "Item " << i + 1 << " Value: ";
        cin >> items[i].value;
        cout << "Item " << i + 1 << " Weight: ";
        cin >> items[i].weight;
        
        if (items[i].weight > 0) {
            items[i].ratio = items[i].value / items[i].weight;
        } else {
            items[i].ratio = 0;
        }
    }

    double profitMinWeight = runKnapsackStrategy(items, capacity, "Minimum Weight First", cmpMinWeight);
    double profitMaxValue = runKnapsackStrategy(items, capacity, "Maximum Value First", cmpMaxValue);
    double profitMaxRatio = runKnapsackStrategy(items, capacity, "Maximum Unit Value First", cmpMaxRatio);

    cout << "\n====================================================\n";
    cout << setw(35) << left << "Greedy Strategy" << " | " << "Total Profit\n";
    cout << "----------------------------------------------------\n";
    cout << setw(35) << left << "1. Minimum Weight First" << " | " << profitMinWeight << "\n";
    cout << setw(35) << left << "2. Maximum Value First" << " | " << profitMaxValue << "\n";
    cout << setw(35) << left << "3. Maximum Unit Value First (Optimal)" << " | " << profitMaxRatio << "\n";
    cout << "====================================================\n";

    return 0;
}
