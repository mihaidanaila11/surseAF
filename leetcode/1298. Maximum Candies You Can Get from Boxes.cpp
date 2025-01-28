// 34/36 passed

#include <iostream>
#include <vector>
#include <queue>
#define INT_MAX 2147483647

using namespace std;

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int nrBoxes = status.size();

        vector<vector<int>> graph(nrBoxes + 2, vector<int>(nrBoxes+2, 0));

        int sourceNode = nrBoxes;
        int sinkNode = nrBoxes + 1;

        for(auto& box : initialBoxes){
            graph[sourceNode][box] = candies[box];
        }

        for(int i=0; i<nrBoxes; i++){
            graph[i][sinkNode] = candies[i];
        }

        vector<bool> vis(nrBoxes+1, false);
        vector<bool> gasit(nrBoxes+1, false);
        
        return edmondsKarp(graph, sourceNode, sinkNode, status, candies, keys, containedBoxes);

    }

private:
    bool bfs(const vector<vector<int>>& graph, int source, int sink,
            vector<int>& parent){
        
        vector<bool> visited(graph.size());
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

    int edmondsKarp(vector<vector<int>> graph, int source, int sink, vector<int>& status, vector<int>& candies,
     vector<vector<int>>& keys, vector<vector<int>>& containedBoxes){
        vector<bool> gasit(keys.size());


        vector<int> parent(graph.size(), -1);
        int maxFlow = 0;

        while(bfs(graph, source, sink, parent)){
            int path_flow = INT_MAX;

            int currentNode = sink;

            while(currentNode != source){
                path_flow = min(path_flow, graph[parent[currentNode]][currentNode]);
                

                if(currentNode != sink){
                    for(auto key : keys[currentNode]){
                        status[key] = 1;
                        if(gasit[key]){
                            graph[source][key] = candies[key];
                        }
                        
                    }
                    for(auto contBox : containedBoxes[currentNode]){
                        gasit[contBox] = true;

                        if(status[contBox]){
                            graph[source][contBox] = candies[contBox];
                        }
                    }
                }

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
};

int main(){

    Solution s;
    vector<int> status = {1,0,1,0};
    vector<int> candies={7,5,4,100};
    vector<vector<int>> keys ={{},{},{1},{}};
    vector<vector<int>> containedBoxes = {{1,2},{3},{},{}};
    vector<int> initialBoxes = {0};
    s.maxCandies(
        status, candies, keys, containedBoxes, initialBoxes
        
    );

    return 0;
}