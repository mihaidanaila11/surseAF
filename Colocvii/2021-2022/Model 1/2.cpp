#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <vector>

#define INT_MAX 2147483647

using namespace std;

int minCost;
vector<vector<int>> mstGraph;

int radacina(int x, vector<int>& parent)
{
    if(parent[x] == -1){
        return x;
    }
    parent[x] = radacina(parent[x], parent);
    return parent[x];
}

void reuniune(int x, int y, vector<int>& nrNoduriArbori, vector<int>& parent, int c){
    int radX = radacina(x, parent);
    int radY = radacina(y, parent);

    if(nrNoduriArbori[radX] < nrNoduriArbori[radY]){
        parent[radX] = radY;
        nrNoduriArbori[radY] += nrNoduriArbori[radY];
    }
    else{
        parent[radY] = radX;
        nrNoduriArbori[radX] += nrNoduriArbori[radY];
    }

    mstGraph[radX][radY] = c;
    mstGraph[radY][radX] = c;
}

void kruskal(vector<tuple<int,int,int>> muchii, int n){
    mstGraph = vector<vector<int>>(n+1, vector<int>(n+1, -1));
    vector<int> parent(n+1, -1);
    vector<bool> vis(muchii.size(), false);
    vector<int> nrNoduriArbori(n+1);

    int cost = 0;

    sort(muchii.begin(), muchii.end());

    int nrMuchii = 0;
    int i = 0;

    while(nrMuchii < n-1){
        int x = get<1>(muchii[i]);
        int y = get<2>(muchii[i]);
        int c = get<0>(muchii[i]);

        if(radacina(x, parent) != radacina(y,parent)){
            // cout << "am ales " << x << " " << y << "\n";
            vis[i] = true;
            nrMuchii++;
            cost += c;

            reuniune(x,y, nrNoduriArbori, parent, c);
        }

        i++;
    }

    cout << cost << "\n";
}
int main(){

    ifstream fin("f.in");
    int m,n;

    fin >> n >> m;

    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));

    vector<tuple<int,int,int>> muchii(m);

    for(int i = 1; i<=m; i++){
        int u,v,w;
        fin >> u >> v >> w;
        // graph[u][v] = w;
        // graph[v][u] = w;

       muchii[i-1] = {w,u,v};
    }

    kruskal(muchii, n);

    vector<tuple<int,int,int>> muchiiNoi;
    
    for(int i=0; i<2; i++){
        int u,v,w;
        cin >> u >> v >> w;

        muchiiNoi.emplace_back(w,u,v);
    }

    pair<int,int> costMin = {INT_MAX, -1};
    for(int i=0; i<muchiiNoi.size(); i++){
        int minNod = INT_MAX;
        int nod = get<1>(muchiiNoi[i]);
        for(int i=1; i<=n; i++){
            minNod = min(minNod, mstGraph[nod][i]);
        }
        nod = get<2>(muchiiNoi[i]);
        for(int i=1; i<=n; i++){
            minNod = min(minNod, mstGraph[nod][i]);
        }

        int costNou = minCost - minNod + get<0>(muchiiNoi[i]);
        if(get<0>(costMin) > costNou){
            costMin = {costNou, i};
        }
        
    }

    
    cout << "adaug muchia " << get<1>(muchiiNoi[get<1>(costMin)]) << " " << get<2>(muchiiNoi[get<1>(costMin)]) << "\n";

    return 0;
}