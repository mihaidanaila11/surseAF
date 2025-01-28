//  graf neorientat cu n noduri si m muchii.
//  Sa se determine daca are cel putin 2 arbori partiali distincti

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <climits>
using namespace std;

vector<set<int>> primMST(vector<vector<int>> graph, int s) {
    int n = graph.size();

    vector<set<int>> adj(n);

    vector<int> parent(n);

    vector<int> key(n);

    vector<bool> vis(n);

    priority_queue<pair<int, int>, 
    vector<pair<int, int>>, 
    greater<pair<int, int>>> pq;

    for (int i = 1; i <= n; i++) {
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
        for (int i = 1; i < n; i++) {
          
            if (!vis[i] && graph[node][i] != 0
                && graph[node][i] < key[i]) {
                    pq.push({graph[node][i], i});
                    key[i] = graph[node][i];
                    parent[i] = node;
                    adj[i].insert(node);
                    adj[node].insert(i);
            }
        }
    }

    return adj;
}

int main() {
    ifstream fin("f.in");
    ofstream fout("f.out");

    int m,n;
    cin >> n >> m;


    vector<vector<int>> graph(n+1, vector<int>(n+1));

    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    vector<vector<set<int>>> adjLists(3);
    int contor = 1;

    bool flag = false;

    for(int i=1;i<=n;i++) {

        vector<set<int>> mst = primMST(graph, i);

        if(mst != adjLists[contor-1]) {
            bool valid = true;
            for(int i=1; i<mst.size(); i++) {
                if(mst[i].empty()) {
                    valid = false;
                }
            }

            if(valid) {
                adjLists[contor] = mst;
                contor++;
            }
        }

        if(contor == 3) {
            flag = true;
            break;
        }
    }

    if(!flag) {
        cout << "Nu";
        return 0;
    }
    cout << "Da\n";

    for(int j=1; j<adjLists.size(); j++) {
        for(int i = 1; i<adjLists[j].size(); i++) {
            //cout << i << " ";
            for(auto& v : adjLists[j][i]) {
                fout << v << " ";
            }
            fout << "\n";
        }
    }

    return 0;
}