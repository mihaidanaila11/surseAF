#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, const vector<vector<int>>& G,
    vector<bool>& vis)
{
    vis[x] = true;

    for (auto i : G[x]){
        if (!vis[i]){
            DFS(i, G, vis);
        }
    }
}

int main(){

    return 0;
}