#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size(), -1);
        for(int i=0; i<graph.size(); i++){
            if(colors[i] == -1){
                if(!col(graph, colors, i)){
                    return false;
                }
            }
        }

        return true;
    }

private:
    bool col(vector<vector<int>>& graph, vector<int>& colors, int node){
        queue<int> q;

        colors[node] = 0;

        q.push(node);

        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(const auto& vecin : graph[u]){
                if(colors[vecin] == -1){
                    colors[vecin] = !colors[u];
                    q.push(vecin);
                }

                else if(colors[vecin] == colors[u]){
                    return false;
                }                
            }
        }

        return true;
    }
};

int main(){

    Solution s;
    vector<vector<int>> graph ={
        {1,3},
        {0,2},
        {1,3},
        {0,2}
    };

    cout << s.isBipartite(graph);

    return 0;
}