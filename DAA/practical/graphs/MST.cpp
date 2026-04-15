#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; 
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;
    vector<Edge> edges;
    
    unordered_map<string, int> nameToIndex;
    vector<string> indexToName;

    void printPath(int curr, const vector<int>& parent) {
        if (curr == -1) return;
        printPath(parent[curr], parent);
        cout << indexToName[curr] << " ";
    }

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addNode(int index, const string& name) {
        nameToIndex[name] = index;
        indexToName.push_back(name);
    }

    void addEdge(const string& u, const string& v, int weight) {
        if (nameToIndex.find(u) == nameToIndex.end() || nameToIndex.find(v) == nameToIndex.end()) {
            cout << "Error: One or both nodes not found!\n";
            return;
        }
        int indexU = nameToIndex[u];
        int indexV = nameToIndex[v];
        
        adj[indexU].push_back({indexV, weight});
        adj[indexV].push_back({indexU, weight});
        edges.push_back({indexU, indexV, weight});
    }

    void kruskalMST() {
        if (V <= 1) return;

        int totalCost = 0;
        vector<Edge> sortedEdges = edges; 
        
        sort(sortedEdges.begin(), sortedEdges.end());
        
        DSU dsu(V);
        int edgesIncluded = 0;

        cout << "\n--- Kruskal's Minimum Spanning Tree ---\n";
        
        for (const auto& edge : sortedEdges) {
            if (dsu.find(edge.u) != dsu.find(edge.v)) {
                dsu.unite(edge.u, edge.v);
                totalCost += edge.weight;
                edgesIncluded++;
                
                cout << "Edge Included: " << indexToName[edge.u] << " - " 
                     << indexToName[edge.v] << " | Weight: " << edge.weight << "\n";
                     
                if (edgesIncluded == V - 1) break;
            }
        }
        
        cout << "---------------------------------------\n";
        cout << "Total Minimum Spanning Tree Cost: " << totalCost << "\n";
    }

    void primMST(const string& startNodeName) {
        if (nameToIndex.find(startNodeName) == nameToIndex.end()) {
            cout << "Error: Start node not found.\n";
            return;
        }
        
        int startNode = nameToIndex[startNodeName];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> key(V, INT_MAX);    
        vector<int> parent(V, -1);      
        vector<bool> inMST(V, false);   
        
        pq.push({0, startNode});
        key[startNode] = 0;
        
        int totalCost = 0;

        cout << "\n--- Prim's Minimum Spanning Tree ---\n";
        cout << "(Starting from node '" << startNodeName << "')\n";

        while (!pq.empty()) {
            int u = pq.top().second;
            int w = pq.top().first;
            pq.pop();

            if (inMST[u]) continue;
            
            inMST[u] = true;
            totalCost += w;

            if (parent[u] != -1) {
                cout << "Edge Included: " << indexToName[parent[u]] << " - " 
                     << indexToName[u] << " | Weight: " << w << "\n";
            }

            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }
        
        cout << "------------------------------------\n";
        cout << "Total Minimum Spanning Tree Cost: " << totalCost << "\n";
    }

    void dijkstra(const string& startNodeName) {
        if (nameToIndex.find(startNodeName) == nameToIndex.end()) {
            cout << "Error: Start node not found.\n";
            return;
        }

        int startNode = nameToIndex[startNodeName];
        
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1); 
        
        vector<bool> inS(V, false); 

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[startNode] = 0;
        pq.push({0, startNode});

        cout << "\n--- Dijkstra's Shortest Path ---\n";
        cout << "(Starting from node '" << startNodeName << "')\n";

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inS[u]) continue;
            
            inS[u] = true;

            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second; 

                if (!inS[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v}); 
                }
            }
        }

        for (int i = 0; i < V; i++) {
            if (i == startNode) continue;
            
            cout << "To " << indexToName[i] << " | Cost: ";
            if (dist[i] == INT_MAX) {
                cout << "INF (Unreachable)\n";
            } else {
                cout << dist[i] << " | Path: ";
                printPath(i, parent);
                cout << "\n";
            }
        }
        cout << "--------------------------------\n";
    }
};

int main() {
    int n, e;
    cout << "Enter the number of nodes: ";
    cin >> n;

    Graph g(n);

    cout << "Enter the names of the " << n << " nodes:\n";
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        g.addNode(i, name);
    }

    cout << "Enter the number of edges: ";
    cin >> e;

    cout << "Enter the edges (Node1 Node2 Weight):\n";
    for (int i = 0; i < e; i++) {
        string u, v;
        int weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    int choice;
    do {
        cout << "\n========== Graph Algorithms Menu ==========\n";
        cout << "1. Run Kruskal's Algorithm (MST)\n";
        cout << "2. Run Prim's Algorithm (MST)\n";
        cout << "3. Run Dijkstra's Algorithm (Shortest Path)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.kruskalMST();
                break;
            case 2: {
                string startNode;
                cout << "Enter the starting node for Prim's algorithm: ";
                cin >> startNode;
                g.primMST(startNode);
                break;
            }
            case 3: {
                string startNode;
                cout << "Enter the starting node for Dijkstra's algorithm: ";
                cin >> startNode;
                g.dijkstra(startNode);
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}