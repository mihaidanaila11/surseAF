#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

#define INT_MAX 2147483647

using namespace std;

vector<set<int>> primMST(vector<vector<int>> graph, int s) {
    int n = graph.size();

    vector<set<int>> adj(n);

    vector<int> parent(n, -1);

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

    // parent[s] = -1;

    pq.push({0, s});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        vis[node] = true;
        for (int i = 1; i < n; i++) {

            if (!vis[i] && graph[node][i] != 0
                && graph[node][i] < key[i]) {
                pq.push({graph[node][i], i});
                key[i] = graph[node][i];
                parent[i] = node;
                adj[node].insert(i);
                adj[i].insert(node);
            }
        }
    }

    // cout << "Muchie \tCost\n";
    // for (int i = 0; i < n; i++) {
    //     cout << parent[i] << " - " << i 
    //       << " \t" << graph[i][parent[i]] << " \n";
    // }

    int cost = 0;
    for(int i=1; i<n; i++){
        if(i != s){
            cost += key[i];
        }
    }

    // cout << cost;

    return adj;
}

int main(){

    

    int n,m;
    cin >> n >> m;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    for(int i = 0; i<m; i++){
        int u,v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    vector<vector<set<int>>> arbori(3);
    bool flag = false;

    int contor = 1;
    for(int i=1; i<=n; i++){
        vector<set<int>> adj = primMST(graph, i);

        //verificam daca e arbore valid
        int muchiiFolosite = 0;
        for(int j=1; j<=n; j++){
            muchiiFolosite += adj[j].size();
        }

        if(muchiiFolosite != (n-1)*2){
            continue;
        }

        if(adj != arbori[contor-1]){
            arbori[contor] = adj;
            contor++;
        }

        if(contor == 3){
            flag = true;
            break;
        }
    }

    if(!flag){
        cout << "Nu\n";
        return 0;
    }
   
    cout << "Da\n";

    
    
    for(int a = 1; a<arbori.size(); a++){
        vector<unordered_map<int,int>> vis(n+1);
        for(int i = 1; i<=n; i++){
            for(const auto node : arbori[a][i]){
                if(vis[i][node] != 1){
                    cout << i << " " << node << "\n";
                    vis[node][i] = 1;
                }
                
            }
        }
    }

    return 0;
}