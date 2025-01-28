//  problema de flux maxim - n persoane m centre cu nr limitat de doze
//  care e nr minim de persoane care nu se pot vaccina?

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

bool bfs(const vector<vector<int>>& graph, int source, int sink,
        vector<int>& parent){
    
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while(!q.empty()){
        int node = q.front();
        q.pop();

        for(int u = 0; u < graph.size(); u++){
            if(!visited[u] && graph[node][u] != 0){
                q.push(u);
                parent[u] = node;
                visited[u] = true;
            }
        }
    }

    return visited[sink];
}

int edmondsKarp(vector<vector<int>> graph, int source, int sink){
    vector<int> parent(graph.size(), -1);
    int maxFlow = 0;

    while(bfs(graph, source, sink, parent)){
        int path_flow = 2147483647;

        int currentNode = sink;

        while(currentNode != source){
            path_flow = min(path_flow, graph[parent[currentNode]][currentNode]);
            currentNode = parent[currentNode];
        }



        maxFlow += path_flow;

        currentNode = sink;
        while(currentNode != source){
            int parinte = parent[currentNode];
            graph[currentNode][parinte] += path_flow;
            graph[parinte][currentNode] -= path_flow;
            currentNode = parent[currentNode];
        }
        
    }

    return maxFlow;
}

int main(){

    int n,m;
    cin >> n >> m;

    vector<int> doze;

    for(int i=0; i<m; i++){
        int doza;
        cin >> doza;
        doze.push_back(doza);
    }

    vector<vector<int>> graph(n+m+2, vector<int>(n+m+2, 0));

    for(int i=1; i<=n; i++){
        int nrCentre;
        cin >> nrCentre;

        for(int j=0; j<nrCentre; j++){
            int centru;
            cin >> centru;
            graph[i][centru+n] = 1;
            graph[0][i] = 1;
        }
    }

    for(int i=n+1; i<=n+m; i++){
        graph[i][n+m+1] = doze[i-n-1];
    }

    // for(auto l : graph){
    //     for(auto c : l){
    //         cout << c << " ";
    //     }
    //     cout << "\n";
    // }

    cout << n-edmondsKarp(graph, 0,n+m+1);
    // vector<int> parent(graph.size(), -1);
    // cout << bfs(graph,0,n+m+1, parent);

    return 0;
}