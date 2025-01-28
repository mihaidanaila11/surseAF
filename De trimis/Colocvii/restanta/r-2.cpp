#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>

using namespace std;

int radacina(int x, vector<int>& parent)
{
    if(parent[x] == -1){
        return x;
    }
    parent[x] = radacina(parent[x], parent);
    return parent[x];
}

void reuniune(int x, int y, vector<int>& nrNoduriArbori, vector<int>& parent){
    int radX = radacina(x, parent);
    int radY = radacina(y, parent);

    if(nrNoduriArbori[radX] < nrNoduriArbori[radY]){
        parent[radX] = radY;
        nrNoduriArbori[radY] += nrNoduriArbori[radX];
    }
    else{
        parent[radY] = radX;
        nrNoduriArbori[radX] += nrNoduriArbori[radY];
    }
}

int kruskal(vector<tuple<int,int,int>> muchii, int n){
    vector<int> parent(n+1, -1);
    vector<bool> vis(muchii.size(), false);
    vector<int> nrNoduriArbori(n+1);

    int cost = 0;

    //sort(muchii.begin(), muchii.end());

    int nrMuchii = 0;
    int i = 0;

    while(nrMuchii < n-1){
        int x = get<1>(muchii[i]);
        int y = get<2>(muchii[i]);
        int c = get<0>(muchii[i]);

        if(radacina(x, parent) != radacina(y,parent)){
            vis[i] = true;
            nrMuchii++;
            cost += c;

            reuniune(x,y, nrNoduriArbori, parent);
        }

        i++;
    }

    return cost;
}

int kruskalFortat(vector<tuple<int,int,int>> muchii, int n, tuple<int,int,int> muchieFortata,
int costInitial){
    vector<int> parent(n+1, -1);
    vector<bool> vis(muchii.size(), false);
    vector<int> nrNoduriArbori(n+1);

    

    //sort(muchii.begin(), muchii.end());



    int nrMuchii = 0;
    int cost = 0;
    int i = 0;

    {
        int x = get<1>(muchieFortata);
        int y = get<2>(muchieFortata);
        int c = get<0>(muchieFortata);

        vis[i] = true;
        nrMuchii++;
        cost += c;

        reuniune(x,y, nrNoduriArbori, parent);
    }

    while(nrMuchii < n-1){
        int x = get<1>(muchii[i]);
        int y = get<2>(muchii[i]);
        int c = get<0>(muchii[i]);

        if(radacina(x, parent) != radacina(y,parent)){
            vis[i] = true;
            nrMuchii++;
            cost += c;

            if(cost > costInitial){
                return cost;
            }

            reuniune(x,y, nrNoduriArbori, parent);
        }

        i++;
    }

    return cost;
}

int main(){

    fstream fin("f.in");

    int n,m;
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

    vector<tuple<int,int,int>> muchiiSortate = muchii;
    sort(muchiiSortate.begin(), muchiiSortate.end());

    int cost = kruskal(muchiiSortate,n);

    int nrTeste;
    fin >> nrTeste;

    for(int i=0; i<nrTeste; i++){
        int muchie;
        fin >> muchie;

        int costFortat = kruskalFortat(muchiiSortate, n, muchii[muchie-1], cost);

        if(cost == costFortat){
            cout << "Da\n";
        }
        else{
            cout << "Nu\n";
        }
    }
    
    return 0;
}