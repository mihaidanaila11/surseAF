#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
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
        q.pop();

        for(int u = 1; u < graph.size(); u++){
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

    return maxFlow;
}

int main(){
    ifstream fin("f.in");
    int m,n,p;

    fin >> n >> m >> p;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    for(int i=0; i<m; i++){
        int x,y,z;

        fin >> x >> y >> z;
        graph[x][y] = z;
    }

    int fluxA = edmondsKarp(graph, 1, n);
    cout << fluxA << "\n";

    int fluxMax = 0;

    for(int i=1; i<=n; i++){
        if(graph[1][i] != 0){
            graph[1][i] += p;
            int flux = edmondsKarp(graph, 1, n);
            fluxMax = max(fluxMax, flux-fluxA);
            graph[1][i] -= p;
        }
    }

    cout << fluxMax << "\n";

    return 0;
}