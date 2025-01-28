#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

int h, copiiRad;

void dfs(int x, int p, int radacina, vector<int>& vis, vector<vector<int>> graph,
vector<int>& d, vector<int>& min_level, unordered_set<int>& articulatii) {
    vis[x] = 1;
    h++;
    d[x] = min_level[x] = h;
    for(auto next : graph[x]) {
        if(!vis[next]) {
            dfs(next, x, radacina, vis, graph, d, min_level, articulatii); 
            min_level[x] = min(min_level[x], min_level[next]); 
            if(x == radacina) { 
                copiiRad++;
            } else {
                if(min_level[next] >= d[x]) { // conditie nod critic
                    articulatii.insert(x);
                }
            }
        } else {
            if(next != p) {
                min_level[x] = min(min_level[x], d[next]);
            }
        }
    }
}

int main() {

        int n, m;
        cin >> n >> m;

        vector<vector<int>> graph(n+1);

        for(int i=0; i<m; i++) { // citim muchiile
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
;
        int r = 1;
        copiiRad = 0;
        unordered_set<int> art;   // daca e nevoie pot sa fac si cu vector de lungime n+1 initializat cu 0
                        // si sa pun 1 pt nodurile care sunt noduri critice
        vector<int> vis(n+1, 0), d(n+1, 0), min_level(n+1);
        dfs(r, 0, r, vis, graph, d, min_level, art);
        if(copiiRad >= 2) { // daca radacina are mai mult de 2 copii, e punct de articulatie
            art.insert(r);
        }

        for(const auto& nod : art) {
            cout << nod << " ";
        }

    return 0;
}