#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define INT_MAX 2147483647

using namespace std;

bool bfs(const vector<vector<int>>& graph, int source, int sink,
        vector<int>& parent){
    
    vector<bool> visited(graph.size());
    queue<int> q;

    q.push(source); 
    visited[source] = true;

    while(!q.empty()){
        int node = q.front();
        // cout << "sunt in " << node << "\n";
        q.pop();

        for(int u = 1; u < graph.size(); u++){
            if(!visited[u] && graph[node][u] != 0){
                q.push(u);
                // cout << "pun " << u << "\n";
                parent[u] = node;
                visited[u] = true;
            }
        }
    }

    return visited[sink];
}

void dfs(vector<vector<int>> graph, int nod, vector<bool>& vizitat) {
    vizitat[nod] = true;
    for(int i=1; i<graph.size(); i++) {
        if(!vizitat[i] && graph[nod][i] > 0) {
            dfs(graph, i, vizitat);
        }
    }
}

int edmondsKarp(vector<vector<int>> graph, int source, int sink, vector<vector<int>> conexiuni){ // O(nm^2)
    vector<int> parent(graph.size(), -1);
    int maxFlow = 0;

    while(bfs(graph, source, sink, parent)){
        int path_flow = INT_MAX;

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


    // taieturi minime
    vector<bool> vis(graph.size(), false);
    dfs(graph, source, vis);

    for(int i=1; i<graph.size(); i++){
        for(int j=1; j<graph.size(); j++){
            if(vis[i] && !vis[j] && graph[j][i] > 0 && conexiuni[i][j] != 0) {
                cout << i << " " << j << " " << "\n";
            }
        }
    }
    return maxFlow;
}

int main(){

    ifstream fin("f.in");

    int n,m;
    fin >> n >> m;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
    

    for(int i=0; i<m; i++){
        int u,v,w;
        fin >> u >> v >> w;

        graph[u][v] = w;
    }

    vector<vector<int>> conexiuni = graph;

    cout << edmondsKarp(graph, 1, 8, conexiuni);

    return 0;
}