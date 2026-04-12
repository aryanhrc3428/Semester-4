#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

class DirectedGraph {
private:
    int V;
    vector<vector<int>> adj;           
    vector<vector<int>> undirected_adj; 
    unordered_map<string, int> nameToIndex;
    vector<string> indexToName;

public:
    DirectedGraph(int vertices) {
        V = vertices;
        adj.resize(V);
        undirected_adj.resize(V);
    }

    void addNode(int index, const string& name) {
        nameToIndex[name] = index;
        indexToName.push_back(name);
    }

    void addEdge(const string& u, const string& v) {
        if (nameToIndex.find(u) == nameToIndex.end() || nameToIndex.find(v) == nameToIndex.end()) {
            cout << "Error: One or both nodes not found!\n";
            return;
        }
        int indexU = nameToIndex[u];
        int indexV = nameToIndex[v];

        adj[indexU].push_back(indexV);

        undirected_adj[indexU].push_back(indexV);
        undirected_adj[indexV].push_back(indexU);
    }

    void BFS(const string& startNode) {
        if (nameToIndex.find(startNode) == nameToIndex.end()) return;
        
        int start = nameToIndex[startNode];
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal (Directed): ";
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << indexToName[curr] << " ";

            for (int neighbor : adj[curr]) { 
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    void DFS(const string& startNode) {
        if (nameToIndex.find(startNode) == nameToIndex.end()) return;

        int start = nameToIndex[startNode];
        vector<bool> visited(V, false);
        stack<int> s;

        s.push(start);

        cout << "DFS Traversal (Directed): ";
        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            if (!visited[curr]) {
                cout << indexToName[curr] << " ";
                visited[curr] = true;
            }

            for (auto it = adj[curr].rbegin(); it != adj[curr].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
        cout << "\n";
    }

    void findWeaklyConnectedComponents() {
        vector<bool> visited(V, false);
        int componentCount = 0;

        cout << "Weakly Connected Components:\n";
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                
                queue<int> q;
                visited[i] = true;
                q.push(i);

                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    cout << indexToName[curr] << " ";

                    for (int neighbor : undirected_adj[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                cout << "\n";
            }
        }
    }

    bool isBipartite() {
        vector<int> color(V, -1); 

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;

                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();

                    for (int neighbor : undirected_adj[curr]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[curr];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[curr]) {
                            return false; 
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    int n, e;
    cout << "Enter the number of nodes: ";
    cin >> n;

    DirectedGraph g(n);

    cout << "Enter the names of the " << n << " nodes:\n";
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        g.addNode(i, name);
    }

    cout << "Enter the number of edges: ";
    cin >> e;

    cout << "Enter the connections (From To):\n";
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "\n--- Directed Graph Operations ---\n";
    
    if (n > 0) {
        string startNode;
        cout << "Enter the starting node for BFS/DFS: ";
        cin >> startNode;

        g.BFS(startNode);
        g.DFS(startNode);
    }

    cout << "\n";
    g.findWeaklyConnectedComponents();

    cout << "\nBipartite Test: ";
    if (g.isBipartite()) {
        cout << "The graph IS Bipartite.\n";
    } else {
        cout << "The graph is NOT Bipartite.\n";
    }

    return 0;
}