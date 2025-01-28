#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

int radacina(vector<vector<int>>& graph, vector<int> p, int x){
    while(p[x] != -1){
        x = p[x];
    }

    return x;
}



bool col(vector<vector<int>>& graph, vector<int>& colors, int node, vector<bool>& cicluA){
        queue<int> q;

        colors[node] = 0;

        vector<int> p(graph.size(), -1);

        q.push(node);

        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(const auto& vecin : graph[u]){
                if(colors[vecin] == -1){
                    colors[vecin] = !colors[u];
                    p[vecin] = u;
                    q.push(vecin);
                }

                else if(colors[vecin] == colors[u]){
                    if(radacina(graph, p, vecin) == radacina(graph, p, u)){
                        vector<int> path1, path2;

                        int current = vecin;
                        while(current != -1){
                            path1.push_back(current);
                            cicluA[current] = true;
                            current = p[current];
                        }


                        current = u;
                        while(current != -1){
                            path2.push_back(current);
                            cicluA[current] = true;
                            current = p[current];
                        }

                        for(int i=1; i<path1.size(); i++){
                            cout << path1[i-1] << " " << path1[i] << "\n";
                        }

                        for(int i=path2.size()-2; i>=0; i--){
                            cout << path2[i+1] << " " << path2[i] << "\n";
                        }
                        cout << vecin << " " << u << "\n\n";
                        return false;
                    }
                    
                }                
            }
        }

        return true;
    }

bool flag = false;

void DFS(vector<vector<int>>& graph, int x, vector<bool>& vis, vector<int> p, vector<bool>& cicluA){
    // Marcarea nodului curent ca vizitat
    vis[x] = true;

    // Recursivitatea pentru vizitarea nodurilor adiacente
    for (auto i : graph[x]){
        if (!vis[i]){
            p[i] = x;
            DFS(graph, i, vis, p, cicluA);
            if(flag){
                return;
            }
        }
        else{
            // ciclu
            if(p[x] == i){
                continue;
            }
            vector<bool> cicluB(cicluA.size(), false);
            cicluB[i] = true;

            int current = x;
            while(current != -1){
                cicluB[current] = true;
                current = p[current];
            }
            
            if(cicluA != cicluB){
                current = x;
                while(current != i){
                    cout << current << " " << p[current] << "\n";
                    current = p[current];
                }

                cout << i << " " << x << "\n";

                flag = true;
                return;
            }
        }
    }
}

int main(){

    ifstream fin("f.in");

    int n, m;
    fin >> n >> m; // Citirea numarului de noduri si muchii

    vector<vector<int>> graph(n+1);

    // Citirea muchiilor si construirea listei de adiacenta
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    // 
    // vector<int>d(n+1, 0);
    

    vector<bool> cicluA(n+1, false);

    vector<int> colors(n+1, -1);
        for(int i=1; i<=n; i++){
            if(colors[i] == -1){
                if(col(graph, colors, i, cicluA)){
                    cout << "nu s-a gasit\n";
                }
            }
        }

    vector<int>p(n+1, -1);
    vector<bool>vis(n+1, false);

    DFS(graph, 1, vis, p, cicluA);

    return 0;
}