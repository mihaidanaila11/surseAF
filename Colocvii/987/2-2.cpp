//  graf orientat aciclic si k destinatii
//  sa se determine un drum de lungime maxima care se termina
//  in una din cele k destinatii

// se face cu ordinea topologica

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

stack<int> st;

void DFS(int x, const vector<vector<int>>& G,
    vector<bool>& vis)
{
    vis[x] = true;

    for (auto i : G[x]){
        if (!vis[i]){
            DFS(i, G, vis);
        }
    }
    st.push(x);
}

vector<int> topologic(const vector<vector<int>>& G){
    vector<bool> vis(G.size(), false);
    for(int i=1; i<G.size(); i++){
        if(!vis[i]){
            DFS(i, G, vis);
        }
    }

    vector<int> sort;


    while(!st.empty()){
        int node = st.top();
        sort.push_back(node);
        st.pop();
    }

    return sort;
}

int main() {
    ifstream fin("f.in");
    ofstream fout("f.out");

    int m,n, k;
    cin >> n >> m >> k;


    vector<int> destinatii;

    for(int i = 0; i < k; i++) {
        int dest;
        cin >> dest;
        destinatii.push_back(dest);
    }


    vector<vector<int>> graph(n+1);

    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;

        graph[u].push_back(v);
        //graph[v][u] = 1;
    }


    vector<int> sort = topologic(graph);

    vector<int> d(n+1, -1);
    vector<int> parent(n+1, -1);
    
    for(const auto node : sort){
        if(d[node] == -1){
            d[node] = 0;
        }

        for(const auto v : graph[node]){
            //d[v] = max(d[v], d[node]+1);
            if(d[v] < d[node]+1){
                d[v] = d[node] + 1;
                parent[v] = node;
            }
        }
    }

    int maxLen = -1;
    int index;

    for(const auto i : destinatii){
        if(maxLen < d[i]){
            maxLen = d[i];
            index = i;
        }
    }

    cout << maxLen << "\n";

    vector<int> path;
    while(index != -1){
        path.push_back(index);
        index = parent[index];
    }

    for(int i=path.size()-1; i>=0; i--){
        cout << path[i] << " ";
    }
    return 0;
}