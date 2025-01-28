#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<bool> vis(isConnected.size(), false);

        int componente = 0;

        for(int i=0; i<isConnected.size(); i++){
            if(!vis[i]){
                dfs(isConnected, vis, i);
                componente++;
            }
        }

        return componente;
    }

private:
    void dfs(vector<vector<int>>& graph, vector<bool>& vis, int s){
        vis[s] = true;

        for(int i=0; i<graph.size(); i++){
            if(graph[s][i] != 0 && !vis[i]){
                dfs(graph, vis, i);
            }
        }
    }
};

int main(){

    Solution s;
    vector<vector<int>> graph ={
        {1,0,1},
        {1,1,0},
        {0,0,1}
    };

    cout << s.findCircleNum(graph);
    
    return 0;
}