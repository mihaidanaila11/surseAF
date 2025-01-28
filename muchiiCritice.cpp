#include <iostream>
#include <algorithm>
#include <vector>

#define INT_MAX 2147483647

using namespace std;

int dfs(int i, int p, vector<int>& niv, int k,
	    vector<vector<int>> adj, vector<vector<int> >& muchiiCrit,
		vector<int>& vis)
{
	niv[i] = k;

	vis[i] = 1;

	int niv_min = INT_MAX;

	for (auto nod : adj[i]) {
		if (nod != p) {
			if (vis[nod]) {
				niv_min = min(niv_min, niv[nod]);
			}
			else {
				int minRank = dfs(nod, i, niv, k + 1, adj,
								muchiiCrit, vis);
				if (niv[i] < minRank) {
					muchiiCrit.push_back({ i, nod });
				}
				niv_min = min(minRank, niv_min);
			}
		}
	}
	return niv_min;
}

vector<vector<int> > muchiiCritice(vector<vector<int>> adj)
{
    int V = adj.size();
	vector<vector<int> > muchiiCrit;
	vector<int> niv(V, -1), vis(V, 0);
	dfs(1, -1, niv, 0, adj, muchiiCrit, vis);

	return muchiiCrit;
}

int main()
{

	vector<vector<int>> adj{
        {},
        {2,3},
        {1},
        {1}
    };
	// for (int i = 0; i < m; i++) {
	// 	adj[edges[i][0]].push_back(edges[i][1]);
	// 	adj[edges[i][1]].push_back(edges[i][0]);
	// }
	vector<vector<int> > muchiiCrit = muchiiCritice(adj);
	for (int i = 0; i < muchiiCrit.size(); i++) {
		cout << muchiiCrit[i][0] << " " << muchiiCrit[i][1] << endl;
	}
	return 0;
}
