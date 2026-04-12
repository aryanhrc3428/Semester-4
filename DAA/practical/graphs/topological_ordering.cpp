#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<int> inDegree;
    unordered_map<string, int> nameToIndex;
    vector<string> indexToName;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        inDegree.assign(V, 0);
    }

    void addNode(int index, const string& name) {
        nameToIndex[name] = index;
        indexToName.push_back(name);
    }

    void addEdge(const string& u, const string& v) {
        if (nameToIndex.find(u) == nameToIndex.end() || nameToIndex.find(v) == nameToIndex.end()) {
            cout << "Error: Nodes not found.\n";
            return;
        }
        int idxU = nameToIndex[u];
        int idxV = nameToIndex[v];
        
        adj[idxU].push_back(idxV);
        inDegree[idxV]++; 
    }

    bool isDAG() {
        vector<int> tempInDegree = inDegree;
        queue<int> q;
        int visitedCount = 0;

        for(int i = 0; i < V; i++) {
            if(tempInDegree[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            int u = q.front();
            q.pop();
            visitedCount++;

            for(int v : adj[u]) {
                tempInDegree[v]--;
                if(tempInDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return visitedCount == V;
    }

    void findAllTopologicalOrdersUtil(vector<int>& res, vector<bool>& visited, vector<int>& currentInDegree) {
        bool flag = false; 

        for (int i = 0; i < V; i++) {
            if (!visited[i] && currentInDegree[i] == 0) {
                
                visited[i] = true;
                res.push_back(i);
                
                for (int neighbor : adj[i]) {
                    currentInDegree[neighbor]--;
                }

                findAllTopologicalOrdersUtil(res, visited, currentInDegree);

                visited[i] = false;
                res.pop_back();
                for (int neighbor : adj[i]) {
                    currentInDegree[neighbor]++;
                }

                flag = true;
            }
        }

        if (!flag) {
            if (res.size() == V) {
                cout << "[ ";
                for (int idx : res) {
                    cout << indexToName[idx] << " ";
                }
                cout << "]\n";
            }
        }
    }

    void printAllTopologicalSorts() {
        vector<bool> visited(V, false);
        vector<int> res;
        vector<int> currentInDegree = inDegree; 

        cout << "\nAll Possible Topological Orderings:\n";
        findAllTopologicalOrdersUtil(res, visited, currentInDegree);
    }
};

int main() {
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;

    Graph g(n);
    cout << "Enter node names:\n";
    for(int i=0; i<n; i++) {
        string s;
        cin >> s;
        g.addNode(i, s);
    }

    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter connections (From To):\n";
    for(int i=0; i<e; i++) {
        string u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "\n----------------------------------------\n";
    cout << "Step 1: Verifying Graph Properties...\n";

    if (g.isDAG()) {
        cout << "Result: A valid topological ordering exists.\n";
        cout << "Proof: Since a topological sort is possible, the graph contains NO cycles.\n";
        cout << "Conclusion: The graph IS a DAG.\n";
        
        g.printAllTopologicalSorts();
    } else {
        cout << "Result: Unable to complete topological sort (Cycle detected).\n";
        cout << "Proof: Topological ordering is undefined for Cyclic Graphs.\n";
        cout << "Conclusion: The graph is NOT a DAG.\n";
    }

    return 0;
}