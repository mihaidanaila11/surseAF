#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

stack<int> st;

void DFS(int x, const vector<vector<int>>& G,
    vector<bool>& vis)
{
    vis[x] = true;

    for (auto i : G[x])
    {
        if (!vis[i])
        {
            DFS(i, G, vis);
        }
    }
    st.push(x);
}

void topologic(const vector<vector<int>>& G){
    vector<bool> vis(G.size(), false);
    for(int i=1; i<G.size(); i++){
        if(!vis[i]){
            DFS(i, G, vis);
        }
    }

    while(!st.empty()){
        cout << st.top();
        st.pop();
    }
}

int main(){
    ifstream fin("f.in");
    ofstream fout("f.out");

    

    int m,n;
    fin >> n >> m;

    vector<vector<int>> G(n+1);

    for (int i = 0; i < m; i++) {
        int u,v;
        fin >> u >> v;

        G[u].push_back(v);
        //G[v][u] = 1;
    }

    topologic(G);

    return 0;
}