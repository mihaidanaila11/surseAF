#include <iostream>
#include <vector>
#include <queue>

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
}

int main(){

    return 0;
}