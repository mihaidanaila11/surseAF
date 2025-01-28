#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#define INT_MAX 2147483647
using namespace std;

void primMST(vector<vector<int>> graph, int s) {
    int n = graph.size();

    vector<int> parent(n);

    vector<int> key(n);

    vector<bool> vis(n);

    priority_queue<pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>> pq;

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        vis[i] = false;
    }

    key[s] = 0;

    parent[s] = -1;

    pq.push({0, s});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        vis[node] = true;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && graph[node][i] != 0
                && graph[node][i] < key[i]) {
                pq.push({graph[node][i], i});
                key[i] = graph[node][i];
                parent[i] = node;
            }
        }
    }

    // cout << "Edge \tWeight\n";
    // for (int i = 0; i < n; i++) {
    //     cout << parent[i] << " - " << i 
    //       << " \t" << graph[i][parent[i]] << " \n";
    // }

    int cost = 0;
    for(int i=1; i<n; i++){
        if(i != s){
            cout << i << " " << key[i] << "\n";
            cost += key[i];
        }
    }

    cout << cost;
}

int main() {

    ifstream fin("f.in");

    int n,m;
    fin >> n >> m;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    for(int i = 0; i<m; i++){
        int u,v,w;
        fin >> u >> v >> w;
        graph[u][v] = w;
       // graph[v].push_back(u);
    }

    for(auto l : graph){
        for(auto c : l ){
            cout << c << " ";
        }
        cout << "\n";
    }

    primMST(graph, 1);

    return 0;
}