#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void bfs(const vector<vector<int>>& graph, int source, int c){
    
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    queue<int> q;

    vector<bool> fromC(graph.size(), false);
    fromC[c] = true;

    vector<int> asc, desc;

    q.push(source);
    visited[source] = true;

    while(!q.empty()){
        int node = q.front();
        q.pop();

        for(const auto u : graph[node]){
            if(!visited[u]){
                q.push(u);
                parent[u] = node;
                visited[u] = true;

                if(fromC[node]){
                    fromC[u] = true;
                    desc.push_back(u);
                }
            }
        }
    }

    int node = parent[c];

    while(node != -1){
        asc.push_back(node);
        node = parent[node];
    }

    if(asc.empty()){
        cout << 0;
    }
    else{
        for(const auto a : asc){
            cout << a << " ";
        }
    }

    cout << "\n";

    if(desc.empty()){
        cout << 0;
    }
    else{
        for(const auto d : desc){
            cout << d << " ";
        }
    }
    cout << "\n";
}

int main(){

    // ifstream cin("f.in");

    int n,r,c;
    cin >> n >> r >> c;

    vector<vector<int>> graph(n+1);

    for(int i = 0; i<n-1; i++){
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


    bfs(graph, r, c);

    return 0;
}