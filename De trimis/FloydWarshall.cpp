#include <iostream>
#include <vector>
#include <fstream>

#define INT_MAX 2147483647

using namespace std;

vector<vector<int>> FloydWarshall(vector<vector<int>> graph){
    int n = graph.size();
    vector<vector<int>> d = graph;
    vector<vector<int>> p(n, vector<int>(n, 0));
    for(int i=1; i<n; i++){
        for(int j=1; j<n; j++){
            if(graph[i][j] != INT_MAX){
                p[i][j]=i;
            }
            else if(i == j){
                d[i][j] = 0;
            }
            else{
                p[i][j] = 0;
            }
        }
    }

    for(int k=1; k<n; k++){
        for(int i=1; i<n; i++){
            for(int j=1; j<n; j++){
                if(d[i][j] > d[i][k] + d[k][j] && (d[i][k]!= INT_MAX && d[k][j] != INT_MAX)){
                    //cout << "adun " << d[i][k]  << " " <<  d[k][j] << " pe " << i << " " << j << "\n";
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }

    return d;
}

int main(){

    ifstream fin("f.in");

    int n,m;
    fin >> n >> m;

    vector<vector<int>> graph(n+1, vector<int>(n+1, INT_MAX));
    

    for(int i=0; i<m; i++){
        int u,v,w;
        fin >> u >> v >> w;

        graph[u][v] = w;
    }

    

    vector<vector<int>> d = FloydWarshall(graph);

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }


    return 0;
}